# P.U.R.A. - Plataforma de Utilização e Recirculação da Água 💧

A **PURA** é um sistema de baixo custo para **captar, armazenar e reutilizar a água de solos úmidos**.  
O objetivo é aproveitar a água que infiltra no solo após chuvas fortes, evitando desperdício e garantindo reserva para uso posterior.

---

## 🔧 Como funciona?
1. O **sensor de umidade do solo** detecta quando o solo está **encharcado**.
2. O **Arduino** recebe o sinal do sensor.
3. Se as condições forem atendidas, o Arduino aciona a **bomba de vácuo** através de um **relé**.
4. A água é conduzida do **extrator de soluções do solo** até um **reservatório**.
5. (Opcional) Um módulo de **filtragem** pode tornar a água potável.

---

## 📂 Estrutura do repositório
- `docs/` → Documentação, fluxogramas e instruções  
- `hardware/` → Protoboard, lista de componentes e esquemas eletrônicos  
- `firmware/` → Código para o Arduino controlar bomba + sensores  
- `software/` → Futuro painel de monitoramento (opcional)  

---

## 🛠️ Componentes necessários
- Arduino Uno (ou compatível)
- Protoboard + jumpers
- Sensor de umidade do solo
- Bomba de vácuo 12V
- Relé para acionamento da bomba
- Extrator de soluções do solo
- Fonte de energia (bateria ou adaptador ou direto na tomada)
- Mangueiras e reservatório
- (Opcional) Filtros de purificação de água
