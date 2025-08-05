% run_trunk_lid_tests.m
%
% Script para testar automaticamente o modelo Simulink ECU_Trunk_Lid_Logic_Model.slx
% Baseado na lógica de acionamento do atuador da tampa do porta-malas.
% Gera um arquivo XML para Xray (formato JUnit).

clear; clc; % Limpa o workspace e a command window

% --- 1. Definir os Cenários de Teste ---
% Cada linha é um cenário:
% {Remote_Trunk_Open_Command, Internal_Trunk_Open_Command, KL30_ON, Vehicle_Status, KL15_ON, Engine_ON, EXPECTED_Trunk_Lid_Signal}
test_scenarios = {
    % Positivos (Output = 1)
    1, 0, 1, 0, 0, 0, 1; % Test 1: Remote ON, Parked, Ignition/Engine OFF
    0, 1, 1, 0, 0, 0, 1; % Test 2: Internal ON, Parked, Ignition/Engine OFF
    1, 1, 1, 0, 0, 0, 1; % Test 3: Both ON, Parked, Ignition/Engine OFF
    1, 0, 1, 0, 1, 0, 1; % Test 4: Remote ON, Parked, Engine OFF (KL15 ON OK)
    0, 1, 1, 0, 0, 1, 1; % Test 5: Internal ON, Parked, Ignition OFF (Engine ON OK)
    1, 0, 1, 0, 0, 1, 1; % Test 6: Remote ON, Parked, Ignition OFF (Engine ON OK)

    % Negativos (Output = 0)
    0, 0, 1, 0, 0, 0, 0; % Test 7: NO command
    1, 0, 0, 0, 0, 0, 0; % Test 8: KL30 OFF (no basic power)
    1, 0, 1, 1, 0, 0, 0; % Test 9: Vehicle MOVING (Vehicle_Status = 1)
    1, 0, 1, 0, 1, 1, 0; % Test 10: KL15 ON AND Engine ON (vehicle "ready to drive")
    0, 0, 0, 0, 0, 0, 0; % Test 11: All OFF
    1, 0, 0, 1, 1, 1, 0; % Test 12: No conditions met, KL30 OFF + moving + running
};

num_tests = size(test_scenarios, 1);
results = cell(num_tests, 1); % Para armazenar os resultados de cada teste

modelName = 'ECU_Trunk_Lid_Logic_Model'; % Nome do seu arquivo .slx sem a extensão

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
    % CORREÇÃO AQUI: Usar test_scenarios(i,:) para acessar a linha completa
    current_scenario = test_scenarios(i,:); 

    % Extrair as entradas e a saída esperada para o cenário atual
    Remote_Trunk_Open_Command_input = current_scenario{1};
    Internal_Trunk_Open_Command_input = current_scenario{2};
    KL30_ON_input                   = current_scenario{3};
    Vehicle_Status_input            = current_scenario{4};
    KL15_ON_input                   = current_scenario{5};
    Engine_ON_input                 = current_scenario{6};
    expected_Trunk_Lid_Signal       = current_scenario{7};

    % Criando Timeseries e Dataset para as entradas
    t = [0; 0.001]; % Tempos para o timeseries
    
    % Os nomes das timeseries DEVEM corresponder EXATAMENTE aos nomes dos Inports no seu modelo!
    Remote_Trunk_Open_Command_ts = timeseries(boolean([Remote_Trunk_Open_Command_input; Remote_Trunk_Open_Command_input]), t, 'Name', 'Remote_Trunk_Open_Command');
    Internal_Trunk_Open_Command_ts = timeseries(boolean([Internal_Trunk_Open_Command_input; Internal_Trunk_Open_Command_input]), t, 'Name', 'Internal_Trunk_Open_Command');
    KL30_ON_ts                   = timeseries(boolean([KL30_ON_input; KL30_ON_input]), t, 'Name', 'KL30_ON');
    Vehicle_Status_ts            = timeseries(boolean([Vehicle_Status_input; Vehicle_Status_input]), t, 'Name', 'Vehicle_Status'); % Vehicle_Status agora é BOOLEAN
    KL15_ON_ts                   = timeseries(boolean([KL15_ON_input; KL15_ON_input]), t, 'Name', 'KL15_ON');
    Engine_ON_ts                 = timeseries(boolean([Engine_ON_input; Engine_ON_input]), t, 'Name', 'Engine_ON');

    input_dataset = Simulink.SimulationData.Dataset;
    input_dataset = input_dataset.addElement(Remote_Trunk_Open_Command_ts);
    input_dataset = input_dataset.addElement(Internal_Trunk_Open_Command_ts);
    input_dataset = input_dataset.addElement(KL30_ON_ts);
    input_dataset = input_dataset.addElement(Vehicle_Status_ts);
    input_dataset = input_dataset.addElement(KL15_ON_ts);
    input_dataset = input_dataset.addElement(Engine_ON_ts);

    % Configurar a simulação com o Dataset de entrada
    in = Simulink.SimulationInput(modelName);
    in = in.setExternalInput(input_dataset);
    
    % Nome descritivo para o testcase no XML
    testcase_name = sprintf('Test_%02d_RemoteTrunkCmd_%d_InternalTrunkCmd_%d_KL30_%d_VehStatus_%d_KL15_%d_Eng_%d', ...
        i, Remote_Trunk_Open_Command_input, Internal_Trunk_Open_Command_input, KL30_ON_input, ...
        Vehicle_Status_input, KL15_ON_input, Engine_ON_input);

    % String para o testcase atual (acumulada em memória)
    current_testcase_xml = sprintf('    <testcase classname="%s" name="%s">\n', modelName, testcase_name);

    % Simular o modelo
    try
        simOut = sim(in);

        % O nome da saída DEVE corresponder EXATAMENTE ao nome do Outport no seu modelo!
        actual_Trunk_Lid_Signal = simOut.logsout.getElement('Trunk_Lid_Signal').Values.Data(end);

        if actual_Trunk_Lid_Signal == expected_Trunk_Lid_Signal
            status = 'PASSED';
            msg = '';
        else
            status = 'FAILED';
            msg = sprintf('Saída incorreta. Esperado: %d, Obtido: %d', expected_Trunk_Lid_Signal, actual_Trunk_Lid_Signal);
            current_testcase_xml = [current_testcase_xml, sprintf('      <failure message="%s"/>\n', escapeXml(msg))]; % Adiciona a falha
            num_failed_xml = num_failed_xml + 1;
        end
    catch ME
        status = 'ERROR';
        msg = ME.message;
        actual_Trunk_Lid_Signal = -1; % Indica erro ou valor padrão em caso de exceção
        
        current_testcase_xml = [current_testcase_xml, sprintf('      <error message="Erro durante a simulação: %s"/>\n', escapeXml(msg))]; % Adiciona o erro
        num_errors_xml = num_errors_xml + 1;

        disp('--- ERRO DURANTE A SIMULAÇÃO ---');
        disp(['Detalhes do erro: ', ME.message]);
    end

    current_testcase_xml = [current_testcase_xml, '    </testcase>\n']; % Fecha o testcase
    xml_testcase_strings{i} = current_testcase_xml; % Salva a string XML do testcase

    results{i} = struct(...
        'scenario_num', i, ...
        'inputs', struct('Remote_Trunk_Open_Command', Remote_Trunk_Open_Command_input, ...
                         'Internal_Trunk_Open_Command', Internal_Trunk_Open_Command_input, ...
                         'KL30_ON', KL30_ON_input, ...
                         'Vehicle_Status', Vehicle_Status_input, ...
                         'KL15_ON', KL15_ON_input, ...
                         'Engine_ON', Engine_ON_input), ...
        'expected', expected_Trunk_Lid_Signal, ...
        'actual', actual_Trunk_Lid_Signal, ...
        'status', status, ...
        'message', msg);

    fprintf('Cenário %2d: RemoteTrunkCmd=%d, InternalTrunkCmd=%d, KL30=%d, VehStatus=%d, KL15=%d, Eng=%d -> Saída: %d (Esp: %d) - %s %s\n', ...
            i, Remote_Trunk_Open_Command_input, Internal_Trunk_Open_Command_input, KL30_ON_input, ...
            Vehicle_Status_input, KL15_ON_input, Engine_ON_input, actual_Trunk_Lid_Signal, expected_Trunk_Lid_Signal, status, msg);
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
fprintf(fileID, '<testsuites name="ECU_Trunk_Lid_Logic_Tests" tests="%d" failures="%d" errors="%d">\n', num_tests, num_failed_xml, num_errors_xml);
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