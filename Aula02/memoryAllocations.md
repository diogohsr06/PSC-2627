# ALOCAÇÃO DE MEMÓRIA

## - Estática:
  ■ Variáveis com tempo de vida global;  
  ■ (Existem desde o carregamento do programa ou módulo até ao seu fim).  
  ```text
  **Ex: int x = 5**  
```

## - Automática: 
  ■ Variáveis locais e argumentos de função;  
    - Alocação por ajuste do STACK_POINTER na entrada da função;  
    - Reposição do STACK_POINTER á saída.  
  
## - Dinâmica: 
  ■ Objetos alocados explicitamente.  
  ■ struct student *ps = malloc(sizeof(struct student));  
  **Ex**  
  ```text
  Kotlin  
  class Student(val num: Int)  
  var s = Student(1234)  
          |___________|  
                |  
       Aloca dinamicamente  
        uma instância de  
            Student  
  
  C:  
  struct student {  
      ...  
  };  
  struct student s = {1234, "Pedro"};  
                 => Instância de student  
  struct student *ps = &s;  
                |____| => Operador que indica o endereço do Objeto  
                   |  
          referência explicita  
              para student  
```
