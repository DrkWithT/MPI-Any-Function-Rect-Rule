# Grammar

### Brief:
Specifies the grammar production rules for the language of single-variable (x) expressions. However, expression exponents are omitted for simplicity. Thus only polynomial-like functions are supported.

```
literal = number | variable
unary = "-"? literal
power = unary "^" literal
factor = power (("*" | "/") power)*
term = factor (("+" | "-") factor)*
expr = term
```
