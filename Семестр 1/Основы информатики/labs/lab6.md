## Вспомогательная структура данных — поток (stream)

```scheme
;; Конструктор потока
(define (make-stream items . eos)
  (if (null? eos)
      (make-stream items #f)
      (list items (car eos))))

;; Запрос текущего символа
(define (peek stream)
  (if (null? (car stream))
      (cadr stream)
      (caar stream)))

;; Запрос первых двух символов
(define (peek2 stream)
  (if (null? (car stream))
      (cadr stream)
      (if (null? (cdar stream))
          (list (caar stream))
          (list (caar stream) (cadar stream)))))

;; Продвижение вперёд
(define (next stream)
  (let ((n (peek stream)))
    (if (not (null? (car stream)))
        (set-car! stream (cdr (car stream))))
    n))

(define (expect stream term error)
    (if (equal? (peek stream) term)
        (next stream)
        (error #f)))    
```


## Задание 1

### `check-frac`

#### БНФ

```
<frac>            ::= <signed-num> / <unsigned-num>
<signed-num>      ::= + <unsigned-num> | - <unsigned-num> | <unsigned-num>
<unsigned-num>    ::= <num-tail>
<num-tail>        ::= <num-tail> | <empty>
<empty>           ::=
```

#### Код

```scheme

(define (check-frac str)
  (load "stream.scm") 

  (define (signed-num stream error)
    (cond ((equal? #\+ (peek stream))
           (next stream)
           (unsigned-num stream error))
          ((equal? #\- (peek stream))
           (next stream)
           (unsigned-num stream error))
          (else (unsigned-num stream error))))
  
  (define (unsigned-num stream error)
    (cond ((and (char? (peek stream))
                (char-numeric? (peek stream)))
           
           (next stream)
           (num-tail stream error))
          (else (error #f))))
  
  (define (frac stream error)
    (signed-num stream error)
    (expect stream #\/ error)
    (unsigned-num stream error))   
  
  (define (num-tail stream error)
    (cond ((and (char? (peek stream))
                (char-numeric? (peek stream)))
           (next stream)
           (num-tail stream error))
          (else #t)))
  
  ;; создаем поток
  (define stream (make-stream (string->list str) 'EOF))
  
  ;; Создаём точку возврата
  (call-with-current-continuation
   (lambda (error)
     (frac stream error)
     (eqv? (peek stream) 'EOF))))

(display (check-frac "1/2"))     ;; #t
(newline)
(display (check-frac "inf/2"))   ;; #f
(newline)
(display (check-frac "1/ui"))    ;; #f
(newline)
(display (check-frac "oi/dd"))   ;; #f
(newline)
(display (check-frac "12"))      ;; #f
(newline)
(display (check-frac ""))        ;; #f

```

### `scan-frac`

#### БНФ

```
<frac>            ::= <signed-num> / <unsigned-num>
<signed-num>      ::= + <unsigned-num> | - <unsigned-num> | <unsigned-num>
<unsigned-num>    ::= <num-tail>
<num-tail>        ::= <num-tail> | <empty>
<empty>           ::=
```

#### Код

```scheme
(define (scan-frac str)
  (load "stream.scm")

  (define (signed-num stream error)
    (cond ((equal? #\+ (peek stream))
           (next stream)
           (unsigned-num stream error))
          ((equal? #\- (peek stream))
           (next stream)
           (- (unsigned-num stream error)))
          (else (unsigned-num stream error))))
  
  (define (unsigned-num stream error)
    (cond ((and (char? (peek stream))
                (char-numeric? (peek stream)))
           (string->number (list->string
                            (cons (next stream)
                                  (num-tail stream error)))))
          (else (error #f))))
  
  (define (num-tail stream error)
    (cond ((and (char? (peek stream))
                (char-numeric? (peek stream)))
           (cons (next stream)
                 (num-tail stream error)))
          (else '())))
  
  (define (frac stream error)
    (define numerator (signed-num stream error))
    (expect stream #\/ error)
    (/ numerator
       (unsigned-num stream error))) 
  
  ;; Создаем поток
  (define stream (make-stream (string->list str) 'EOF))

  ;; Создаём точку возврата
  (call-with-current-continuation
   (lambda (error)
     (define res (frac stream error))
     (and (eqv? (peek stream) 'EOF)
          res))))

(display (scan-frac "-1/2"))     ;; -1/2
(newline)
(display (scan-frac "inf/2"))    ;; #f
(newline)
(display (scan-frac "1/ui"))     ;; #f
(newline)
(display (scan-frac "oi/dd"))    ;; #f
(newline)
(display (scan-frac "12"))       ;; #f
(newline)
(display (scan-frac ""))         ;; #f
```

### `scan-many-fracs`

``scheme
(define (scan-many-fracs str)
  (load "stream.scm")
  
  (define (frac-list stream error)
    (cond ((and (char? (peek stream))
                (or (char-whitespace? (peek stream))
                    (equal? (peek stream) #\+)
                    (equal? (peek stream) #\-)
                    (char-numeric? (peek stream))))
           (spaces stream error)
           (let ((new-frac (frac stream error)))
             (spaces stream error)
             (cons new-frac (frac-list stream error))))
          (else '())))
  
  (define (spaces stream error)
    (cond ((and (char? (peek stream))
                (char-whitespace? (peek stream)))
           (next stream)
           (spaces stream error))
          (else #t)))

  (define (signed-num stream error)
    (cond ((equal? #\+ (peek stream))
           (next stream)
           (unsigned-num stream error))
          ((equal? #\- (peek stream))
           (next stream)
           (- (unsigned-num stream error)))
          (else (unsigned-num stream error))))
  
  (define (unsigned-num stream error)
    (cond ((and (char? (peek stream))
                (char-numeric? (peek stream)))
           (string->number (list->string
                            (cons (next stream)
                                  (num-tail stream error)))))
          (else (error #f))))
  
  (define (num-tail stream error)
    (cond ((and (char? (peek stream))
                (char-numeric? (peek stream)))
           (cons (next stream)
                 (num-tail stream error)))
          (else '())))
  
  (define (frac stream error)
    (define numerator (signed-num stream error))
    (expect stream #\/ error)
    (/ numerator
       (unsigned-num stream error)))

  ;; создаем поток
  (define stream (make-stream (string->list str) 'EOF))

  ;; Создаём точку возврата
  (call-with-current-continuation
   (lambda (error)
     (define res (frac-list stream error))
     (and (eqv? (peek stream) 'EOF)
          res))))

(display (scan-many-fracs "\t1/2 1/3\n\n10/8"))   ;; (1/2 1/3 5/4)
(newline)
```
