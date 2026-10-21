# Bibliografia canônica por tema

Referências renomadas para citar nos slides, mapeadas aos temas teóricos **[T-n]** do `plano-de-aulas.md`. Cite no formato autor–título–ano; nos slides de conceito, marque a fonte no rodapé.

## [T-1] Frameworks

- JOHNSON, R.; FOOTE, B. *Designing Reusable Classes*. Journal of Object-Oriented Programming, 1988. (origem do conceito de framework e da "inversão de controle")
- FOWLER, M. *Inversion of Control Containers and the Dependency Injection pattern*. martinfowler.com, 2004.

## [T-2] Modelo cliente-servidor

- TANENBAUM, A.; VAN STEEN, M. *Distributed Systems: Principles and Paradigms*. 4ª ed., 2023.
- KUROSE, J.; ROSS, K. *Computer Networking: A Top-Down Approach*. 8ª ed., Pearson, 2021. (cap. 2 — camada de aplicação)

## [T-3] REST e URIs

- FIELDING, R. *Architectural Styles and the Design of Network-based Software Architectures*. Tese de doutorado, UC Irvine, 2000. (cap. 5 — a definição original de REST)
- RFC 3986 — *Uniform Resource Identifier (URI): Generic Syntax*. IETF, 2005.
- RICHARDSON, L.; RUBY, S. *RESTful Web Services*. O'Reilly, 2007.

## [T-4] Ciclo de vida de uma requisição e DNS

- KUROSE, J.; ROSS, K. *Computer Networking: A Top-Down Approach*. (seções de HTTP e DNS)
- RFC 1034 / RFC 1035 — *Domain Names*. IETF, 1987.
- RFC 9110 — *HTTP Semantics*. IETF, 2022.

## [T-5] Servidores web

- KUROSE, J.; ROSS, K. *Computer Networking: A Top-Down Approach*. (servidores HTTP)
- Especificação ASGI — asgi.readthedocs.io (o contrato entre uvicorn e FastAPI).

## [T-6] Gerenciamento de dependências

- HUNT, A.; THOMAS, D. *The Pragmatic Programmer*. 20th Anniversary ed., 2019. (reuso e ortogonalidade)
- PRESTON-WERNER, T. *Semantic Versioning 2.0.0*. semver.org.

## Orientação a objetos (aula extra 01.2)

- DAHL, O.-J.; NYGAARD, K. *SIMULA 67 Common Base Language*. Norwegian Computing Center, 1968. (origem de classe, objeto e herança)
- KAY, A. *The Early History of Smalltalk*. ACM HOPL-II, 1993. (quem cunhou "object-oriented programming")
- BOOCH, G. *Object-Oriented Analysis and Design with Applications*. 3ª ed., Addison-Wesley, 2007. (objeto = estado, comportamento e identidade)
- PARNAS, D. *On the Criteria To Be Used in Decomposing Systems into Modules*. CACM, 1972. (ocultamento de informação — a raiz do encapsulamento)
- LISKOV, B. *Data Abstraction and Hierarchy*. OOPSLA, 1987. (princípio da substituição)
- GAMMA, E.; HELM, R.; JOHNSON, R.; VLISSIDES, J. *Design Patterns*. Addison-Wesley, 1994. ("favor object composition over class inheritance")
- STRACHEY, C. *Fundamental Concepts in Programming Languages*. 1967; CARDELLI, L.; WEGNER, P. *On Understanding Types, Data Abstraction, and Polymorphism*. ACM Computing Surveys, 1985. (polimorfismo)
- RAMALHO, L. *Fluent Python*. 2ª ed., O'Reilly, 2022. (modelo de dados do Python, *dunder methods*, duck typing)
- PEP 8, PEP 318 (decorators), PEP 484 (type hints), PEP 526 (anotações de variáveis), PEP 3115 (metaclasses) — python.org.
- Documentação oficial do Python — *Classes* (docs.python.org/3/tutorial/classes.html).

## [T-7] ORMs

- FOWLER, M. *Patterns of Enterprise Application Architecture*. Addison-Wesley, 2002. (Active Record, Data Mapper, Unit of Work — a base conceitual do SQLAlchemy)
- Documentação oficial do SQLAlchemy — docs.sqlalchemy.org.

## Relações 1:N e modelagem de dados (aulas 05–06, aprofundamento do T-7)

- CHEN, P. *The Entity-Relationship Model — Toward a Unified View of Data*. ACM Transactions on Database Systems, 1976. (entidades, relacionamentos e cardinalidades 1:1, 1:N, N:M)
- DATE, C. J. *An Introduction to Database Systems*. 8ª ed., Addison-Wesley, 2003. (chave estrangeira e integridade referencial)
- Documentação oficial do SQLAlchemy — docs.sqlalchemy.org (`relationship()` e rotas aninhadas).

## [T-8] Autenticação e JWT

- RFC 7519 — *JSON Web Token (JWT)*. IETF, 2015.
- RFC 6265 — *HTTP State Management Mechanism*. IETF, 2011. (cookies e sessions)
- PROVOS, N.; MAZIÈRES, D. *A Future-Adaptable Password Scheme*. USENIX, 1999. (o bcrypt)
- OWASP. *JSON Web Token Cheat Sheet* e *Authentication Cheat Sheet*. cheatsheetseries.owasp.org.

## Frontend: SPA, React, CORS e o token no navegador (Bloco 3)

- GARRETT, J. J. *Ajax: A New Approach to Web Applications*. Adaptive Path, 2005. (a origem das aplicações de página única)
- DIJKSTRA, E. W. *On the role of scientific thought* (EWD 447), 1974. (separação de responsabilidades — pages, components e services)
- PARNAS, D. *On the Criteria To Be Used in Decomposing Systems into Modules*. CACM, 1972. (ocultação de informação — cada módulo esconde uma decisão)
- KOBLENTZ, T. *Challenging CSS Best Practices*. Smashing Magazine, 2013. (Atomic CSS, a origem do utility-first); WATHAN, A. *CSS Utility Classes and "Separation of Concerns"*. adamwathan.me, 2017.
- Bibliotecas de estilo e de componentes: Bootstrap (getbootstrap.com; Otto e Thornton, Twitter, 2011), Tailwind Plus (tailwindcss.com/plus), Headless UI (headlessui.com), daisyUI (daisyui.com), Flowbite (flowbite.com), shadcn/ui (ui.shadcn.com).
- W3C WAI. *Forms Tutorial: Labeling Controls*; W3C. *WCAG 2.1*, 2018 — critério 2.4.7 *Focus Visible*. (acessibilidade de formulários)
- Documentação oficial do React — react.dev (*Thinking in React*, *Describing the UI*, *Managing State*; Jordan Walke, Facebook, JSConf US 2013)
- Documentação oficial do Vite — vite.dev; do Tailwind CSS — tailwindcss.com; do npm — docs.npmjs.com.
- RFC 6454 — *The Web Origin Concept*. IETF, 2011. (a definição de origem: esquema, host e porta)
- W3C. *Cross-Origin Resource Sharing*. W3C Recommendation, 2014; WHATWG. *Fetch Standard* — fetch.spec.whatwg.org. (CORS, preflight e a API fetch)
- RFC 6750 — *The OAuth 2.0 Authorization Framework: Bearer Token Usage*. IETF, 2012. (o header `Authorization: Bearer`)
- WHATWG. *HTML Standard* — seção *Web storage* (localStorage). html.spec.whatwg.org.
- OWASP. *HTML5 Security Cheat Sheet* (Local Storage) e *Cross Site Scripting Prevention Cheat Sheet*. cheatsheetseries.owasp.org.
- MDN Web Docs — *Same-origin policy*, *CORS*, *Fetch API*, *Window: localStorage*. developer.mozilla.org.

## [T-9] Autorização e RBAC

- FERRAIOLO, D.; KUHN, R. *Role-Based Access Controls*. 15th National Computer Security Conference (NIST), 1992. (o paper que definiu RBAC)
- OWASP. *Authorization Cheat Sheet*. cheatsheetseries.owasp.org.

## Testes automatizados (aula 08)

- MYERS, G. *The Art of Software Testing*. Wiley, 1979. (testar é procurar defeitos; caixa preta e caixa branca)
- DIJKSTRA, E. W. *Notes on Structured Programming* (EWD 249), 1970. (o teste mostra a presença de defeitos, nunca a ausência)
- BECK, K. *Simple Smalltalk Testing: With Patterns*, 1994; BECK, K.; GAMMA, E. *Test Infected: Programmers Love Writing Tests*. Java Report, 1998. (a família xUnit)
- BECK, K. *Test-Driven Development: By Example*. Addison-Wesley, 2002. (vermelho e verde)
- WAKE, B. *3A - Arrange, Act, Assert*. xp123.com, 2001.
- COHN, M. *Succeeding with Agile*. Addison-Wesley, 2009; VOCKE, H. *The Practical Test Pyramid*. martinfowler.com, 2018. (a pirâmide de testes)
- ISTQB. *Glossary of Software Testing Terms* - glossary.istqb.org. (unidade, integração, aceitação, regressão)
- MESZAROS, G. *xUnit Test Patterns: Refactoring Test Code*. Addison-Wesley, 2007. (dublês de teste)
- DODDS, K. C. Testing Library - testing-library.com (*Guiding Principles*).
- Documentação oficial do pytest - docs.pytest.org; do Vitest - vitest.dev; do Playwright - playwright.dev; do FastAPI - *Testing* e *Testing Dependencies with Overrides*.

## Consumo de APIs e modelos de linguagem (aula 09)

- WIGGINS, A. *The Twelve-Factor App* - fator III, *Config*. 12factor.net, 2011. (configuração e segredos em variáveis de ambiente)
- DEUTSCH, L. P. *Fallacies of Distributed Computing*. Sun Microsystems, 1994 (a oitava acrescentada por James Gosling, 1997). ("a rede é confiável")
- SHANNON, C. E. *A Mathematical Theory of Communication*. Bell System Technical Journal, 1948. (aproximações do inglês por sequências de letras e palavras)
- RFC 6585 - *Additional HTTP Status Codes*. IETF, 2012. (o 429 Too Many Requests)
- RFC 9110 - *HTTP Semantics*. IETF, 2022. (o 502 Bad Gateway e a semântica do POST)
- OWASP. *Secrets Management Cheat Sheet*. cheatsheetseries.owasp.org.
- JURAFSKY, D.; MARTIN, J. H. *Speech and Language Processing*. 3ª ed., rascunho - web.stanford.edu/~jurafsky/slp3. (a definição de modelo de linguagem)
- VASWANI, A. et al. *Attention Is All You Need*. NeurIPS, 2017. (o Transformer)
- SENNRICH, R.; HADDOW, B.; BIRCH, A. *Neural Machine Translation of Rare Words with Subword Units*. ACL, 2016. (tokens de subpalavra, BPE)
- BROWN, T. et al. *Language Models are Few-Shot Learners*. NeurIPS, 2020. (o GPT-3 e o prompt como forma de programar o modelo)
- OUYANG, L. et al. *Training language models to follow instructions with human feedback*. NeurIPS, 2022. (modelos que seguem instruções)
- JI, Z. et al. *Survey of Hallucination in Natural Language Generation*. ACM Computing Surveys, 2023. (alucinação)
- GEMINI TEAM. *Gemini: A Family of Highly Capable Multimodal Models*. Google DeepMind, arXiv:2312.11805, 2023.
- WILLISON, S. *Prompt injection attacks against GPT-3*. simonwillison.net, 12 set. 2022. (o nome do ataque, demonstrado por Riley Goodside)
- OWASP. *Top 10 for LLM Applications 2025* - LLM01:2025 *Prompt Injection*. genai.owasp.org.
- WILLARD, B.; LOUF, R. *Efficient Guided Generation for Large Language Models*. arXiv:2307.09702, 2023. (decodificação restrita a um schema)
- JSON Schema - json-schema.org (especificação 2020-12).
- Documentação oficial da Gemini API - ai.google.dev/gemini-api/docs (*API keys*, *Interactions API*, *Structured output*, *Models*, *Pricing*); do httpx2 - github.com/pydantic/httpx2; do pytest - docs.pytest.org (*monkeypatch*).

## [T-10] Upload e multipart/form-data

- RFC 7578 — *Returning Values from Forms: multipart/form-data*. IETF, 2015.
- MDN Web Docs. *FormData* e *Using files from web applications*. developer.mozilla.org.

## Gerais (qualquer aula)

- Documentação oficial do FastAPI — fastapi.tiangolo.com.
- Documentação oficial do Pydantic — docs.pydantic.dev.
- DevSheets. *FastAPI Cheat Sheet* — devsheets.io/sheets/fastapi (consulta rápida; seções de Path Parameters e Query Parameters citadas na aula 02).
- Documentação oficial do React — react.dev.
- MDN Web Docs — developer.mozilla.org (HTTP, JS, formulários).
