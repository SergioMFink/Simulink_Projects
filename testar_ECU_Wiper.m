function testar_ECU_Wiper()
    % Nome do modelo
    modelo = 'Test_Wiper_Model';
    load_system(modelo);

    % Lista de testes: [KL15, Switch_Wiper, Rain_Sensor, Park_Switch, Esperado]
    testes = [
        0 0 0 0 1;
        1 0 0 0 0;
        0 1 0 0 1;
        1 1 0 0 1;
        0 0 1 0 1;
        1 0 1 0 1;
        0 1 1 0 1;
        1 1 1 0 1;
        0 0 0 1 0;
        1 0 0 1 0;
        0 1 0 1 0;
        1 1 0 1 1;
        0 0 1 1 0;
        1 0 1 1 1;
        0 1 1 1 0;
        1 1 1 1 1;
    ];

    num_testes = size(testes, 1);
    num_falhas = 0;

    fprintf('=== Testes %s ===\n', modelo);

    % Arquivo XML para integração com Xray
    xml_filename = 'resultados_testes_wiper.xml';
    fileID = fopen(xml_filename, 'w');
    fprintf(fileID, '<testsuites name="ECU_Wiper_Tests" tests="%d" failures="%%d">\n', num_testes);
    fprintf(fileID, '  <testsuite name="%s" tests="%d" failures="%%d">\n', modelo, num_testes);

    for i = 1:num_testes
        KL15          = testes(i, 1);
        Switch_Wiper  = testes(i, 2);
        Rain_Sensor   = testes(i, 3);
        Park_Switch   = testes(i, 4);
        esperado      = testes(i, 5);

        % Criar timeseries booleanos com tempo
        t = [0; 1];
        KL15_ts         = timeseries(boolean([KL15; KL15]), t);
        Switch_ts       = timeseries(boolean([Switch_Wiper; Switch_Wiper]), t);
        Rain_ts         = timeseries(boolean([Rain_Sensor; Rain_Sensor]), t);
        Park_ts         = timeseries(boolean([Park_Switch; Park_Switch]), t);

        % Criar Dataset
        input_dataset = Simulink.SimulationData.Dataset;
        input_dataset = input_dataset.addElement(KL15_ts, 'KL15');
        input_dataset = input_dataset.addElement(Switch_ts, 'Switch_Wiper');
        input_dataset = input_dataset.addElement(Rain_ts, 'Rain_Sensor');
        input_dataset = input_dataset.addElement(Park_ts, 'Park_Switch');

        % Configurar simulação
        in = Simulink.SimulationInput(modelo);
        in = in.setExternalInput(input_dataset);
        in = in.setModelParameter('StopTime', '1');

        % Simular
        out = sim(in);
        sinalOut = out.logsout.get('Wiper_Signal');
        simulado = sinalOut.Values.Data(end);

        % Verificação
        passou = (simulado == esperado);
        if passou
            status = '✅ OK';
        else
            status = '❌ ERRO';
            num_falhas = num_falhas + 1;
        end

        % Nome do teste
        nome_teste = sprintf('Test_%02d_KL15_%d_Switch_%d_Rain_%d_Park_%d', ...
            i, KL15, Switch_Wiper, Rain_Sensor, Park_Switch);

        % Print no console
        fprintf('%s | Entradas: [KL15=%d, Switch_Wiper=%d, Rain_Sensor=%d, Park_Switch=%d] | Esperado: %d | Simulado: %d --> %s\n', ...
            nome_teste, KL15, Switch_Wiper, Rain_Sensor, Park_Switch, esperado, simulado, status);

        % Escrever no XML
        fprintf(fileID, '    <testcase classname="%s" name="%s">\n', modelo, nome_teste);
        if ~passou
            fprintf(fileID, '      <failure message="Saída incorreta detectada."/>\n');
        end
        fprintf(fileID, '    </testcase>\n');
    end

    % Fechar XML
    fprintf(fileID, '  </testsuite>\n');
    fprintf(fileID, '</testsuites>\n');
    fclose(fileID);

    fprintf('=== Testes finalizados ===\n');
    fprintf('Arquivo XML salvo como: %s\n', xml_filename);
end
