# Домашняя работа №2

### Задание 1
```scheme
(define (my-range a b d)
  (if (< a b)
      (cons a (my-range (+ a d) b d))
      '()))


```
