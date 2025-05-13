# 🍷 **Sistema de Monitoramento de Adega para Vinho** 🌡️🛡️  

Um projeto **sofisticado e preciso** para monitorar as condições ideais de armazenamento de vinhos, garantindo **temperatura**, **umidade** e **luminosidade** adequadas para preservar a qualidade dos vinhos.  

---

## 📌 **Por que este projeto?**  
Vinhos exigem condições ambientais específicas:  
- **Temperatura ideal**: 12°C–18°C (varia por tipo de vinho)  
- **Umidade ideal**: 60%–70% (evita ressecamento da rolha)  
- **Baixa luminosidade** (luz excessiva degrada o vinho)  

Este sistema **alerta** quando as condições saem do ideal, protegendo seu investimento!  

---

## 🎯 **Funcionalidades**  
### ✅ **Monitoramento em Tempo Real**  
- **Temperatura** (via sensor DHT22 )  
- **Umidade** (via sensor DHT22)  
- **Luminosidade** (via LDR – evita exposição à luz excessiva)  

### 🚨 **Sistema de Alerta para Adega**  
| Condição                | LED    | Buzzer | Impacto no Vinho |  
|-------------------------|--------|--------|------------------|  
| **Temperatura fora da faixa** (<12°C ou >18°C) | 🔶 Amarelo | 🔊 | Risco de oxidação ou fermentação indesejada |  
| **Umidade fora da faixa** (<60% ou >70%)       | 🔴 Vermelho | 🔊 | Riscos: rolha ressecada ou mofo |  
| **Luminosidade alta** (>600 lux)               | 🔴 Vermelho | 🔊 | Degradação de aromas e cor |  
| **Condições ideais**                           | 🟢 Verde   | ❌  | Vinho seguro! |  

### 📺 **Display LCD 16x2**  
Exibe:  
- Temperatura atual (°C)  
- Umidade (%)  
- Nível de luminosidade (%)  

---

## 🛠 **Componentes Necessários**  
| Componente               | Quantidade | Função no Projeto |  
|--------------------------|------------|-------------------|  
| Arduino (Uno, Nano, etc.) | 1          | Cérebro do sistema |  
| **Sensor DHT22**         | 1          | Mede temp. e umidade com alta precisão |  
| **LDR (Sensor de Luz)**  | 1          | Detecta luminosidade excessiva |  
| **LED RGB**              | 1          | Substitui LEDs individuais (verde/amarelo/vermelho) |  
| **Buzzer Ativo**         | 1          | Alerta sonoro em condições críticas |  
| **Display LCD I2C 16x2** | 1          | Mostra dados em tempo real |  
| **Resistores**           | 4          | 10kΩ (LDR) + 220Ω (LEDs) |  

---


## 🍇 **Como Aplicar na Sua Adega?**  
1. **Instale o sensor DHT22** longe de portas/fontes de calor.  
2. **Posicione o LDR** onde há risco de luz solar/artificial.  
3. **Use o LED RGB** para visualização rápida do status.  
4. **Ajuste os limites** no código conforme o tipo de vinho.  

---

## 📊 **Exemplo de Saída**  
- **LCD**:  
  ```
  Vinho Guardado:  
  14.5°C 65%  
  ```  
- **LED**: Verde (condições perfeitas!)  

---

## 🚀 **Melhorias para Adegas Profissionais**  
- [ ] **Adicionar módulo WiFi** para monitoramento remoto (ex.: ESP8266).  
- [ ] **Integrar relé** para controlar ar-condicionado/umidificador automaticamente.  
- [ ] **Log de dados** em SD card para análise histórica.  

---

## 📜 **Licença**  
MIT License - **Use livremente em sua adega!**  

**Desenvolvido por [Seu Nome]**  

🍾 **Saúde!** Se gostou, compartilhe com outros enófilos! ⭐  

--- 

> 💡 **Dica profissional**: Para vinhos de guarda, mantenha a temperatura entre **12°C–14°C** e umidade em **65%–70%**.