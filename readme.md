# 🖥️ Sistema de Gerenciamento de Falhas em Equipamentos Computacionais

**Pontifícia Universidade Católica de Campinas (PUC-Campinas)**  
**Curso:** Engenharia de Computação  
**Componente Curricular:** Estrutura de Dados (Prática)  
**Projeto:** 2º Projeto Avaliativo - 2026  

---

## 📖 Sobre o Projeto

Este sistema foi desenvolvido na linguagem **C** com o objetivo de registrar equipamentos de laboratório e controlar os incidentes (falhas) associados a eles. O projeto aplica de forma prática e integrada conceitos avançados de alocação dinâmica de memória, manipulação de ponteiros, **Árvores Binárias de Busca (ABB)** e **Tabelas Hash**.

Para evitar sobrecarga no preenchimento de formulários e otimizar buscas, o sistema trabalha com uma base enxuta de informações, mantendo a consistência dos dados nas operações de inclusão, consulta e exclusão em memória.

## 🏗️ Estruturas de Dados Utilizadas

O sistema exige o uso de duas estruturas de dados trabalhando de forma **integrada**:

1. **Tabela Hash (Equipamentos):**
   - Utilizada para acesso rápido aos equipamentos via Código Único (1000 a 9999).
   - Resolução de colisões feita por **encadeamento separado** (listas ligadas).
   - Armazena os dados do equipamento e uma lista encadeada com as referências (IDs) dos incidentes associados a ele.

2. **Árvore Binária de Busca - ABB (Incidentes):**
   - Organiza os incidentes pelo Número Único de Identificação (00 a 99).
   - Permite inserção, busca e listagem ordenada (percurso *In-Order*).
   - Lida com casos de remoção (nó folha, um filho e dois filhos).

**Integração:** Ao consultar um equipamento na Tabela Hash, o sistema percorre sua lista de IDs de incidentes e busca os dados completos desses incidentes diretamente na Árvore Binária.

## ⚙️ Funcionalidades

O programa conta com um menu interativo contendo as seguintes opções:

1. **Cadastrar Equipamento:** Insere um novo equipamento na Tabela Hash.
2. **Registrar Incidente:** Vincula um novo incidente a um equipamento existente, inserindo os dados na Árvore Binária.
3. **Consultar Equipamento e Incidente:** Busca um equipamento pelo código (Hash) e exibe seus dados junto com todos os seus incidentes (Árvore).
4. **Listar todos os Incidentes:** Exibe os incidentes cadastrados em ordem crescente de identificador (Percurso In-Order).
5. **Excluir um Incidente:** Remove o incidente da Árvore Binária (e suas referências).
6. **Excluir um Equipamento:** Remove o equipamento da Hash, garantindo a exclusão prévia de todos os seus incidentes na Árvore.
7. **Encerrar Programa:** Finaliza o sistema liberando **toda** a memória alocada dinamicamente.

## 🚀 Como Executar

O projeto foi construído para ser compatível com a IDE **Code::Blocks**. 

### Pré-requisitos
- Compilador GCC (MinGW) instalado.
- IDE Code::Blocks ou qualquer outro ambiente com suporte à linguagem C.

### Passos para compilação (Via Terminal/GCC)
Caso deseje rodar via terminal de comando, navegue até a pasta dos arquivos fonte e execute:

```bash
gcc -o sistema_falhas main.c bibliotecas.c -Wall
./sistema_falhas
```
*(Nota: Ajuste os nomes dos arquivos `.c` conforme estruturado no projeto).*

## ⚠️ Regras de Negócio e Restrições
- Não é permitido o uso de variáveis globais.
- Não é permitido o uso de funções ou bibliotecas prontas de ordenação.
- Códigos de Equipamento (ID) e Identificadores de Incidente não podem ser duplicados.
- Todo incidente deve estar obrigatoriamente associado a um equipamento existente.
- Toda memória (nós da árvore, da lista e da hash) deve ser rigorosamente liberada (uso de `free()`) no encerramento.

## 👥 Time de Desenvolvimento

- **[Nome do Aluno 1]** - RA: [Inserir RA]
- **[Nome do Aluno 2]** - RA: [Inserir RA]
- **[Nome do Aluno 3]** - RA: [Inserir RA]
- **[Nome do Aluno 4 (Opcional)]** - RA: [Inserir RA]