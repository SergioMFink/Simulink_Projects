% run_bcm_farol_tests_xray_final_robust_xml.m
%
% Script para testar automaticamente o modelo Simulink ECU_Farol_Baixo_Model.slx
% Otimizado para compatibilidade com R2025a Trial, usando a filosofia de Dataset para inputs,
% resolvendo o conflito de logging, e gerando um arquivo XML para Xray (formato JUnit)
% com preenchimento correto de totais de falhas/erros.

clear; clc; % Limpa o workspace e a command window

% --- 1. Definir os Cenários de Teste ---
% Cada linha é um cenário:
% {KL30_ON, Comando_Farol_Baixo, Comando_Farol_Baixo_Automatico, KL15_ON, Engine_ON, EXPECTED_Sinal_Farol_Baixo_ON}
test_scenarios = {
    % Cenários POSITIVOS (Farol Baixo DEVE ligar)
    1, 1, 0, 1, 0, 1; % Manual ON, KL15 ON
    1, 0, 1, 1, 0, 1; % Auto ON, KL15 ON
    1, 1, 0, 0, 1, 1; % Manual ON, Motor ON
    1, 0, 1, 0, 1, 1; % Auto ON, Motor ON
    1, 1, 1, 1, 1, 1; % Tudo ON
    1, 1, 1, 1, 0, 1; % Manual & Auto ON, KL15 ON
    1, 1, 1, 0, 1, 1; % Manual & Auto ON, Engine ON

    % Cenários NEGATIVOS (Farol Baixo NÃO DEVE ligar)
    0, 1, 0, 1, 0, 0; % KL30 OFF (sem energia)
    1, 0, 0, 1, 0, 0; % NENHUM comando de farol (manual ou auto)
    1, 0, 0, 0, 1, 0; % NENHUM comando de farol (manual ou auto)
    1, 1, 0, 0, 0, 0; % Comando manual, mas veículo OFF (KL15 e Motor OFF)
    1, 0, 1, 0, 0, 0; % Comando automático, mas veículo OFF (KL15 e Motor OFF)
    0, 0, 0, 0, 0, 0; % Tudo OFF
    1, 0, 0, 0, 0, 0; % Apenas KL30 ON, sem comandos ou ignição
};

num_tests = size(test_scenarios, 1);
results = cell(num_tests, 1); % Para armazenar os resultados de cada teste

modelName = 'ECU_Farol_Baixo_Model'; % Nome do seu arquivo .slx sem a extensão

% --- 2. Carregar o Modelo Simulink ---
disp(['Carregando o modelo Simulink: ', modelName, '...']);
load_system(modelName); % Abre o modelo (não o torna visível a menos que você peça)

% --- Configurações de Simulação do Modelo ---
set_param(modelName, 'StopTime', '0.001'); % Tempo de simulação mínimo
set_param(modelName, 'Solver', 'FixedStepDiscrete'); % Solucionador discreto para lógica combinacional
set_param(modelName, 'FixedStep', '0.001'); % Passo de tempo fixo

% Resolver o conflito de logging: Desativar "Signal Logging" global
set_param(modelName, 'SignalLogging', 'off');
set_param(modelName, 'SaveOutput', 'on');
set_param(modelName, 'OutputSaveName', 'logsout'); % Assegura que a variável de saída se chama 'logsout'

% --- 3. Preparação para Geração do Arquivo XML (acumulando em memória) ---
xml_testcase_strings = cell(num_tests, 1); % Para armazenar as strings XML de cada testcase
num_failed_xml = 0; % Contador de falhas para o XML
num_errors_xml = 0; % Contador de erros para o XML

% --- 4. Executar os Testes para cada Cenário ---
fprintf('\nIniciando testes para o modelo %s...\n', modelName);
fprintf('-----------------------------------------------------\n');

for i = 1:num_tests
    current_scenario = test_scenarios(i,:);

    % Extrair as entradas e a saída esperada para o cenário atual
    KL30_ON_input                 = current_scenario{1};
    Comando_Farol_Baixo_input     = current_scenario{2};
    Comando_Farol_Baixo_Automatico_input = current_scenario{3};
    KL15_ON_input                 = current_scenario{4};
    Engine_ON_input               = current_scenario{5};
    expected_Sinal_Farol_Baixo_ON = current_scenario{6};

    % Criando Timeseries e Dataset para as entradas
    t = [0; 0.001]; % Tempos para o timeseries
    
    KL30_ON_ts                  = timeseries(boolean([KL30_ON_input; KL30_ON_input]), t, 'Name', 'KL30_ON');
    Comando_Farol_Baixo_ts      = timeseries(boolean([Comando_Farol_Baixo_input; Comando_Farol_Baixo_input]), t, 'Name', 'Comando_Farol_Baixo');
    Comando_Farol_Baixo_Automatico_ts = timeseries(boolean([Comando_Farol_Baixo_Automatico_input; Comando_Farol_Baixo_Automatico_input]), t, 'Name', 'Comando_Farol_Baixo_Automatico');
    KL15_ON_ts                  = timeseries(boolean([KL15_ON_input; KL15_ON_input]), t, 'Name', 'KL15_ON');
    Engine_ON_ts                = timeseries(boolean([Engine_ON_input; Engine_ON_input]), t, 'Name', 'Engine_ON');

    input_dataset = Simulink.SimulationData.Dataset;
    input_dataset = input_dataset.addElement(KL30_ON_ts);
    input_dataset = input_dataset.addElement(Comando_Farol_Baixo_ts);
    input_dataset = input_dataset.addElement(Comando_Farol_Baixo_Automatico_ts);
    input_dataset = input_dataset.addElement(KL15_ON_ts);
    input_dataset = input_dataset.addElement(Engine_ON_ts);

    % Configurar a simulação com o Dataset de entrada
    in = Simulink.SimulationInput(modelName);
    in = in.setExternalInput(input_dataset);
    
    % Nome descritivo para o testcase no XML
    testcase_name = sprintf('Test_%02d_KL30_%d_CmdMan_%d_CmdAuto_%d_KL15_%d_Eng_%d', ...
        i, KL30_ON_input, Comando_Farol_Baixo_input, Comando_Farol_Baixo_Automatico_input, ...
        KL15_ON_input, Engine_ON_input);

    % String para o testcase atual (acumulada em memória)
    current_testcase_xml = sprintf('    <testcase classname="%s" name="%s">\n', modelName, testcase_name);

    % Simular o modelo
    try
        simOut = sim(in);

        actual_Sinal_Farol_Baixo_ON = simOut.logsout.getElement('Sinal_Farol_Baixo_ON').Values.Data(end);

        if actual_Sinal_Farol_Baixo_ON == expected_Sinal_Farol_Baixo_ON
            status = 'PASSED';
            msg = '';
        else
            status = 'FAILED';
            msg = sprintf('Saída incorreta. Esperado: %d, Obtido: %d', expected_Sinal_Farol_Baixo_ON, actual_Sinal_Farol_Baixo_ON);
            current_testcase_xml = [current_testcase_xml, sprintf('      <failure message="%s"/>\n', msg)]; % Adiciona a falha
            num_failed_xml = num_failed_xml + 1;
        end
    catch ME
        status = 'ERROR';
        msg = ME.message;
        actual_Sinal_Farol_Baixo_ON = -1; % Indica erro ou valor padrão em caso de exceção
        
        current_testcase_xml = [current_testcase_xml, sprintf('      <error message="Erro durante a simulação: %s"/>\n', escapeXml(msg))]; % Adiciona o erro
        num_errors_xml = num_errors_xml + 1;

        disp('--- ERRO DURANTE A SIMULAÇÃO ---');
        disp(['Detalhes do erro: ', ME.message]);
    end

    current_testcase_xml = [current_testcase_xml, '    </testcase>\n']; % Fecha o testcase
    xml_testcase_strings{i} = current_testcase_xml; % Salva a string XML do testcase

    results{i} = struct(...
        'scenario_num', i, ...
        'inputs', struct('KL30_ON', KL30_ON_input, ...
                         'Comando_Farol_Baixo', Comando_Farol_Baixo_input, ...
                         'Comando_Farol_Baixo_Automatico', Comando_Farol_Baixo_Automatico_input, ...
                         'KL15_ON', KL15_ON_input, ...
                         'Engine_ON', Engine_ON_input), ...
        'expected', expected_Sinal_Farol_Baixo_ON, ...
        'actual', actual_Sinal_Farol_Baixo_ON, ...
        'status', status, ...
        'message', msg);

    fprintf('Cenário %2d: KL30=%d, CmdMan=%d, CmdAuto=%d, KL15=%d, Eng=%d -> Saída: %d (Esp: %d) - %s %s\n', ...
            i, KL30_ON_input, Comando_Farol_Baixo_input, Comando_Farol_Baixo_Automatico_input, ...
            KL15_ON_input, Engine_ON_input, actual_Sinal_Farol_Baixo_ON, expected_Sinal_Farol_Baixo_ON, status, msg);
end

fprintf('-----------------------------------------------------\n');

% --- 5. Resumo dos Resultados no Console ---
all_statuses = cell(num_tests, 1);
for k = 1:num_tests
    if isfield(results{k}, 'status')
        all_statuses{k} = results{k}.status;
    else
        all_statuses{k} = 'UNKNOWN';
    end
end

num_passed = sum(strcmp(all_statuses, 'PASSED'));
num_failed = sum(strcmp(all_statuses, 'FAILED'));
num_errors = sum(strcmp(all_statuses, 'ERROR'));

fprintf('\nResumo dos Testes:\n');
fprintf('Total de Testes: %d\n', num_tests);
fprintf('Testes Aprovados: %d\n', num_passed);
fprintf('Testes Reprovados: %d\n', num_failed);
fprintf('Testes com Erro: %d\n', num_errors);

% --- 6. Finalização e Escrita do Arquivo XML ---
xml_filename = ['resultados_testes_', modelName, '.xml'];
fileID = fopen(xml_filename, 'w');
if fileID == -1
    error('Não foi possível criar/escrever o arquivo XML: %s', xml_filename);
end

% Escreve o cabeçalho final do XML com os contadores corretos
fprintf(fileID, '<?xml version="1.0" encoding="UTF-8"?>\n');
fprintf(fileID, '<testsuites name="ECU_Farol_Baixo_Tests" tests="%d" failures="%d" errors="%d">\n', num_tests, num_failed_xml, num_errors_xml);
fprintf(fileID, '  <testsuite name="%s" tests="%d" failures="%d" errors="%d">\n', modelName, num_tests, num_failed_xml, num_errors_xml);

% Escreve todas as strings de testcase acumuladas
for k = 1:num_tests
    fprintf(fileID, '%s', xml_testcase_strings{k});
end

% Escreve o rodapé do XML
fprintf(fileID, '  </testsuite>\n');
fprintf(fileID, '</testsuites>\n');
fclose(fileID);

fprintf('\nArquivo XML salvo como: %s\n', xml_filename);

% Fechar o modelo após os testes, se não precisar mais dele
close_system(modelName, 0); % 0 significa não salvar alterações

if num_failed == 0 && num_errors == 0
    disp('TODOS OS TESTES PASSARAM COM SUCESSO!');
else
    disp('ATENÇÃO: ALGUNS TESTES FALHARAM OU APRESENTARAM ERROS.');
end

% --- Função auxiliar para escapar caracteres especiais em XML ---
% Essencial para garantir que mensagens de erro não quebrem o XML.
function str_escaped = escapeXml(str_in)
    str_escaped = strrep(str_in, '&', '&amp;');
    str_escaped = strrep(str_escaped, '<', '&lt;');
    str_escaped = strrep(str_escaped, '>', '&gt;');
    str_escaped = strrep(str_escaped, '''', '&apos;'); % Aspas simples
    str_escaped = strrep(str_escaped, '"', '&quot;');  % Aspas duplas
end