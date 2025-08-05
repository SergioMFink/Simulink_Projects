% Script para testar o circuito lógico Brake_Signal_Model.slx
% Adaptação do script da versão 2025 para passar entradas via Simulink.SimulationInput
% e verificar saídas.
% Adição da geração de arquivo XML para importação no XRAY.

modelName = 'Brake_Signal_Model'; % Verifique se este é o nome exato do seu modelo .slx
xmlFileName = 'XRAY_TestResults.xml'; % Nome do arquivo XML de saída

% Limpa variáveis do workspace
clearvars -except modelName xmlFileName;
clc; % Limpa o Command Window

% Carregar o modelo (se ainda não estiver aberto)
try
    open_system(modelName);
    disp('Modelo aberto com sucesso.');
catch ME
    disp(['Erro ao abrir o modelo ', modelName, '. Verifique se o arquivo .slx está no caminho do MATLAB.']);
    disp(['Detalhes do erro: ', ME.message]);
    return;
end

% As combinações de entrada (KL30, Hill_Signal, Brake_Pedal, Gas_Pedal)
% O fliplr é para alinhar com a ordem dec2bin que gera da direita para a esquerda
combos = dec2bin(0:15) - '0';
combos = logical(fliplr(combos));

totalTests = size(combos, 1);
numErrors = 0;

fprintf('=== Testes %s ===\n', modelName);
fprintf('----------------------------------------------------\n');
fprintf('KL30 | Hill_Signal | Brake_Pedal | Gas_Pedal | Esperado | Obtido | Status\n');
fprintf('----------------------------------------------------\n');

% Definir o tempo para os timeseries (pode ser [0 0] para lógica combinacional pura no tempo 0,
% ou [0 1] se o modelo estiver configurado para simular por um tempo)
tempo = [0 1];

% --- INÍCIO DA CONFIGURAÇÃO DO XML ---
% Cria o nó raiz <testsuites>
docNode = com.mathworks.xml.XMLUtils.createDocument('testsuites');
testsuitesNode = docNode.getDocumentElement;

% Cria o nó <testsuite> para este conjunto de testes
testsuiteNode = docNode.createElement('testsuite');
testsuiteNode.setAttribute('name', ['Testes_' modelName]);
% Os atributos 'tests' e 'failures' serão atualizados no final
testsuitesNode.appendChild(testsuiteNode);
% --- FIM DA CONFIGURAÇÃO DO XML ---

for i = 1:totalTests
    % Atribuir os valores de entrada para a iteração atual
    KL30 = combos(i, 1);
    Hill_Signal = combos(i, 2);
    Brake_Pedal = combos(i, 3);
    Gas_Pedal = combos(i, 4);

    % Criar objetos timeseries para cada entrada
    ts_KL30 = timeseries(logical([KL30 KL30])', tempo');
    ts_Hill = timeseries(logical([Hill_Signal Hill_Signal])', tempo');
    ts_Brake = timeseries(logical([Brake_Pedal Brake_Pedal])', tempo');
    ts_Gas = timeseries(logical([Gas_Pedal Gas_Pedal])', tempo');

    % Criar um Dataset e adicionar os sinais de entrada
    ds = Simulink.SimulationData.Dataset;
    s1 = Simulink.SimulationData.Signal; s1.Name = 'KL30'; s1.Values = ts_KL30;
    s2 = Simulink.SimulationData.Signal; s2.Name = 'Hill_Signal'; s2.Values = ts_Hill;
    s3 = Simulink.SimulationData.Signal; s3.Name = 'Brake_Pedal'; s3.Values = ts_Brake;
    s4 = Simulink.SimulationData.Signal; s4.Name = 'Gas_Pedal'; s4.Values = ts_Gas;
    ds = ds.addElement(s1).addElement(s2).addElement(s3).addElement(s4);

    % Configurar o objeto Simulink.SimulationInput
    simIn = Simulink.SimulationInput(modelName);
    simIn = simIn.setExternalInput(ds); % Define o dataset como entrada externa
    simIn = simIn.setModelParameter('StartTime','0','StopTime','1'); % Simula de 0 a 1 segundo

    % Simular o modelo com o objeto Simulink.SimulationInput
    simOut = sim(simIn);
    
    % --- OBTENÇÃO DA SAÍDA ---
    valorSimulado = NaN; % Inicializa valorSimulado aqui para garantir que exista
    
    try
        yout = simOut.get('yout'); % Pega o Dataset de saída principal
        if ~isempty(yout) && yout.numElements >= 1
            sinalOutFound = false;
            try
                sinalOut = yout.getElement('Brake_Signal');
                sinalOutFound = true;
            catch
                % Tenta pegar o primeiro elemento se 'Brake_Signal' não for encontrado diretamente
                sinalOut = yout.getElement(1);
                if isprop(sinalOut, 'Name') && (strcmp(sinalOut.Name, '1') || strcmp(sinalOut.Name, 'out1'))
                    sinalOutFound = true;
                end
            end

            if sinalOutFound && ~isempty(sinalOut) && isprop(sinalOut, 'Values') && ~isempty(sinalOut.Values) && ~isempty(sinalOut.Values.Data)
                valorSimulado = sinalOut.Values.Data(end); % Pega o último valor do timeseries
            end
        end
    catch ME
        warning(['Erro ao obter saida do modelo (Obtencao): ', ME.message]);
    end
    % --- FIM DA OBTENÇÃO DA SAÍDA ---

    % Calcular o valor esperado de Brake_Signal de acordo com as regras
    esperado = (KL30 && Hill_Signal && ~Brake_Pedal && ~Gas_Pedal) || ...
               (KL30 && Hill_Signal &&  Brake_Pedal && ~Gas_Pedal) || ...
               (KL30 && ~Hill_Signal && Brake_Pedal && ~Gas_Pedal);

    % Comparar o valor obtido com o valor esperado
    isPass = (valorSimulado == esperado);
    status = '✅ OK';
    if ~isPass
        status = '❌ FALHOU';
        numErrors = numErrors + 1;
    end

    % Exibir o resultado do teste no Command Window
    fprintf('Teste %2d | KL30=%d Hill_Signal=%d Brake_Pedal=%d Gas_Pedal=%d | Esperado=%d | Simulado=%d -> %s\n', ...
            i, double(KL30), double(Hill_Signal), double(Brake_Pedal), double(Gas_Pedal), double(esperado), double(valorSimulado), status);
    
    % --- ADIÇÃO DA LÓGICA DE GERAÇÃO DE XML ---
    testcaseNode = docNode.createElement('testcase');
    testcaseNode.setAttribute('name', sprintf('Teste_Combinacao_%d', i));
    testcaseNode.setAttribute('classname', modelName);
    
    if isPass
        testcaseNode.setAttribute('status', 'SUCCESS');
    else
        testcaseNode.setAttribute('status', 'FAILURE');
    end

    % Adicionar propriedades (entradas do teste)
    propertiesNode = docNode.createElement('properties');
    addProperty(propertiesNode, 'KL30', num2str(double(KL30)), docNode);
    addProperty(propertiesNode, 'Hill_Signal', num2str(double(Hill_Signal)), docNode);
    addProperty(propertiesNode, 'Brake_Pedal', num2str(double(Brake_Pedal)), docNode);
    addProperty(propertiesNode, 'Gas_Pedal', num2str(double(Gas_Pedal)), docNode);
    testcaseNode.appendChild(propertiesNode);

    % Adicionar System Output (logs do teste)
    systemOutNode = docNode.createElement('system-out');
    logText = sprintf('Entradas: KL30=%d, Hill_Signal=%d, Brake_Pedal=%d, Gas_Pedal=%d\nEsperado: %d\nObtido: %d', ...
                      double(KL30), double(Hill_Signal), double(Brake_Pedal), double(Gas_Pedal), double(esperado), double(valorSimulado));
    systemOutNode.appendChild(docNode.createCDATASection(logText));
    testcaseNode.appendChild(systemOutNode);

    % Adicionar nó de falha se o teste falhou
    if ~isPass
        failureNode = docNode.createElement('failure');
        failureNode.setAttribute('message', sprintf('O valor simulado (%d) não corresponde ao valor esperado (%d).', double(valorSimulado), double(esperado)));
        testcaseNode.appendChild(failureNode);
    end
    
    testsuiteNode.appendChild(testcaseNode);
    % --- FIM DA ADIÇÃO DA LÓGICA DE GERAÇÃO DE XML ---
end

% Atualizar atributos 'tests' e 'failures' no nó <testsuite>
testsuiteNode.setAttribute('tests', num2str(totalTests));
testsuiteNode.setAttribute('failures', num2str(numErrors));

fprintf('----------------------------------------------------\n');
if numErrors == 0
    disp('Todos os testes foram concluídos com SUCESSO!');
else
    disp(['TOTAL DE ERROS ENCONTRADOS: ', num2str(numErrors), ' de ', num2str(totalTests), ' testes.']);
end

% Salvar o arquivo XML
try
    xmlwrite(xmlFileName, docNode);
    disp(['Resultados do teste exportados para: ', xmlFileName]);
catch ME
    warning(['Erro ao salvar o arquivo XML: ', ME.message]);
end

close_system(modelName, 0); % Fechar o modelo sem salvar alterações

% Função auxiliar para adicionar propriedades ao XML
function addProperty(parentNode, name, value, docNode)
    propertyNode = docNode.createElement('property');
    propertyNode.setAttribute('name', name);
    propertyNode.setAttribute('value', value);
    parentNode.appendChild(propertyNode);
end

%FIM