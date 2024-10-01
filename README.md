# Timer de Pit Stop - Fórmula E 🏎️⏱️

## Descrição

Este projeto consiste em um **Timer de Pit Stop** desenvolvido para simular e registrar o tempo de pit stops durante uma corrida de Fórmula E. Utilizando um microcontrolador **ESP32**, o sistema permite que o usuário inicie e pause o cronômetro, armazenando os tempos de cada pit stop realizado. Ao final, é possível calcular a média dos tempos dos pit stops.

## Funcionalidades

- **Iniciar e Pausar**: Inicie o cronômetro com um botão e pause-o a qualquer momento. 🚦
- **Registro de Pit Stops**: Armazene cada pit stop realizado, exibindo o tempo total em segundos e milissegundos. 📝
- **Cálculo de Média**: Calcule a média dos tempos dos pit stops ao pressionar o botão de reset. 📊
- **Exibição no LCD**: Mostra informações em um display LCD, permitindo fácil leitura durante a operação. 💡

## Componentes Necessários

- **ESP32** 💻
- **Display LCD I2C (16x2)** 📺
- **2 Botões (Push Buttons)** 🔘
- **Resistores de Pull-Up (10kΩ)** 🧩
- **Protoboard e Fios de Conexão** 🔌

## Como Configurar

1. **Instale as Bibliotecas Necessárias**:
   - LiquidCrystal_I2C

2. **Conecte os Componentes**:
   - Conecte o display LCD aos pinos I2C do ESP32.
   - Conecte os botões aos pinos digitais (D2 e D4) do ESP32 com resistores de pull-up.

3. **Carregue o Código**:
   - Faça o upload do código `TimerPitStop.ino` no seu ESP32 usando a IDE Arduino.

4. **Execute o Código**:
   - Abra o monitor serial para verificar a operação do timer e comece a registrar seus pit stops.

## Código

O código está disponível no arquivo `TimerPitStop.ino`. Confira os comentários no código para entender a lógica por trás do funcionamento do timer e como ele gerencia os pit stops.

## Contribuições

Sinta-se à vontade para contribuir com melhorias, correções de bugs ou novas funcionalidades! Para contribuir, siga estas etapas:

1. Faça um fork deste repositório.
2. Crie uma nova branch (`git checkout -b feature/nova-funcionalidade`).
3. Realize suas alterações e faça commit (`git commit -m 'Adiciona nova funcionalidade'`).
4. Envie a branch para o repositório remoto (`git push origin feature/nova-funcionalidade`).
5. Abra um Pull Request.

## Licença

Este projeto está licenciado sob a [MIT License](LICENSE). Desenvolvido pela **Synthica**. 🎉

## Contato

Para mais informações, entre em contato com [Nathan](mailto:nathan.cga@outlook.com). 📧

---

Aproveite seu timer de pit stop e boa corrida na Fórmula E! 🏁
