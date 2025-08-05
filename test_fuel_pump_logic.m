%% Script Completo para Testes FuelPumpControlModel com XML para Xray Jira

clear; clc;

modelName = 'FuelPumpControlModel';

% Carrega o modelo
load_system(modelName);

% Cenários: [Fuel_Level (double), KL15 (bool), Esperado Pump_Control_Signal (bool)]
test_scenarios = [
    0.25, true,  1;
    0.10, true,  1;
    0.00, true,  1;
    0.26, true,  0;
    0.50, true,  0;
    1.00, true,  0;
    0.25, false, 0;
    0.10, false, 0;
    0.00, false, 0;
    0.50, false, 0;
    1.00, false, 0;
    0.30, false, 0;
];

num_tests = size(test_scenarios, 1);

% Configurações do modelo para simulação discreta e logging
set_param(modelName, 'Solver', 'FixedStepDiscrete');
set_param(modelName, 'FixedStep', '0.001');
set_param(modelName, 'StopTime', '0.005');

fprintf('Iniciando testes para %s...\n', modelName);
fprintf('-------------------------------------------------------------\n');
fprintf('%-6s %-12s %-6s %-9s %-9s %-6s\n', 'Teste', 'Fuel_Level', 'KL15', 'Esperado', 'Real', 'Resultado');
fprintf('-------------------------------------------------------------\n');

% Variável para armazenar resultados (para o XML)
results = cell(num_tests, 1);

for i = 1:num_tests
    fuel_val = test_scenarios(i, 1);
    kl15_val = logical(test_scenarios(i, 2));
    expected = logical(test_scenarios(i, 3));
    
    % Cria timeseries para entrada com dois pontos no tempo
    t = [0; 0.001];
    fuel_ts = timeseries([fuel_val; fuel_val], t, 'Name', 'Fuel_Level');
    kl15_ts = timeseries([kl15_val; kl15_val], t, 'Name', 'KL15');
    
    % Cria Dataset com entradas
    input_dataset = Simulink.SimulationData.Dataset;
    input_dataset = input_dataset.addElement(fuel_ts);
    input_dataset = input_dataset.addElement(kl15_ts);
    
    % Prepara a simulação com entrada externa
    simIn = Simulink.SimulationInput(modelName);
    simIn = simIn.setExternalInput(input_dataset);
    
    % Executa simulação
    simOut = sim(simIn);
    
    % Captura saída (supondo Pump_Control_Signal logado no logsout)
    pump_signal = logical(simOut.logsout.get('Pump_Control_Signal').Values.Data(end));
    
    % Resultado
    passed = (pump_signal == expected);
    result_str = ternary(passed, 'PASS', 'FAIL');
    
    % Print detalhado
    fprintf('%-6d %-12.2f %-6d %-9d %-9d %-6s\n', i, fuel_val, kl15_val, expected, pump_signal, result_str);
    
    % Guarda resultado para XML
    results{i} = struct('id', i, ...
                        'fuel', fuel_val, ...
                        'kl15', kl15_val, ...
                        'expected', expected, ...
                        'actual', pump_signal, ...
                        'passed', passed);
end

fprintf('-------------------------------------------------------------\n');
fprintf('Testes concluídos.\n');

% Geração do arquivo XML (JUnit) para Xray Jira

xml_filename = 'resultados_fuel_pump_tests.xml';
fid = fopen(xml_filename, 'w');
if fid == -1
    error('Não foi possível criar o arquivo XML: %s', xml_filename);
end

fprintf(fid, '<?xml version="1.0" encoding="UTF-8"?>\n');
fprintf(fid, '<testsuites name="FuelPumpControlTests" tests="%d">\n', num_tests);
fprintf(fid, '  <testsuite name="%s" tests="%d">\n', modelName, num_tests);

for i = 1:num_tests
    tc = results{i};
    testcase_name = sprintf('Test_%02d_Fuel_%.2f_KL15_%d', tc.id, tc.fuel, tc.kl15);
    fprintf(fid, '    <testcase classname="%s" name="%s">\n', modelName, testcase_name);
    if ~tc.passed
        msg = sprintf('Expected: %d, but got: %d', tc.expected, tc.actual);
        fprintf(fid, '      <failure message="%s"/>\n', xmlEscape(msg));
    end
    fprintf(fid, '    </testcase>\n');
end

fprintf(fid, '  </testsuite>\n');
fprintf(fid, '</testsuites>\n');
fclose(fid);

fprintf('Arquivo XML salvo em: %s\n', xml_filename);

% Fecha modelo sem salvar
close_system(modelName, 0);

% Função auxiliar ternária simples
function out = ternary(cond, valTrue, valFalse)
    if cond
        out = valTrue;
    else
        out = valFalse;
    end
end

% Função auxiliar para escapar caracteres especiais XML
function s = xmlEscape(str)
    s = strrep(str, '&', '&amp;');
    s = strrep(s, '<', '&lt;');
    s = strrep(s, '>', '&gt;');
    s = strrep(s, '"', '&quot;');
    s = strrep(s, '''', '&apos;');
end
