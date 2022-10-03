# Домашняя работа №1

### Определение дня недели по дате
Определите процедуру day-of-week, вычисляющую день недели по дате по григорианскому календарю. Воспользуйтесь алгоритмом, описанным в литературе. Пусть процедура принимает три формальных аргумента (день месяца, месяц и год в виде целых чисел) и возвращает целое число — номер дня в неделе (0 — воскресенье, 1 — понедельник, … 6 — суббота).

```scheme
(define (calendar d m y)
  (remainder (+ d
                (quotient (* 31 m) 12)
                y
                (quotient y 4)
                (- (quotient y 100))
                (quotient y 400))
             7))

(define (day-of-week day month year)
  (if (or (= month 1) (= month 2))
      (calendar day (+ month 10) (- year 1))
      (calendar day (- month 2 ) year)))
```
### Действительные корни квадратного уравнения
Определите процедуру, принимающую коэффициенты a, b и c квадратного уравнения вида /ax/²+/bx/+/c/=0 и возвращающую список чисел — корней уравнения (один или два корня, или пустой список, если корней нет).

```scheme
(define (D a b c)
  (- (* b b)
  (* 4 a c)))

(define (solve_q_by_D a b D)
  (if (>= D 0)
      (if (> D 0)
          (list (/ (+ (- b) (sqrt D)) (* 2 a))
                (/ (- (- b) (sqrt D)) (* 2 a)))
          (list (/ (- b) (* 2 a))))
      (list)))

(define (solve a b c)
  (solve_q_by_D a b (D a b c)))
```

### Проверка на простоту, НОД, НОК
```scheme
(define (prime-test n i)
  (if (<= (* i i) n)
      (if (= (remainder n i) 0)
          #f
          (prime-test n (+ 2 i)))
      #t))

(define (prime? n)
  (if (or (= n 2) (= n 3))
      #t
      (if (and (>= n 5) (> (remainder n 2) 0))
          (prime-test n 3)
          #f)))

(define (my-gcd a b)
  (if (= b 0)
      a
      (my-gcd b (remainder a b))))

(define (my-lcm a b)
  (quotient (* a b) (my-gcd a b)))
```
