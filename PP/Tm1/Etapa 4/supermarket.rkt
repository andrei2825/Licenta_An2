#lang racket
(require racket/match)
(require "queue.rkt")
(require racket/trace)
(provide (all-defined-out))

(define ITEMS 5)
(define-struct counter (index tt et queue status) #:transparent)

; TODO
; Aveți libertatea să vă structurați programul cum doriți (dar cu restricțiile
; de mai jos), astfel încât funcția serve să funcționeze conform specificației.
; 
; Restricții (impuse de checker):
; - trebuie să existe în continuare funcția (empty-counter index)
; - cozile de la case trebuie implementate folosind noul TDA queue

(define (empty-counter index)
  (make-counter index 0 0 empty-queue 1))
  
(define (update f counters index)
  (if (null? counters)
      counters
      (if (not (= (counter-index (car counters)) index))
          (cons (car counters) (update f (cdr counters) index))
          (cons (apply f (list (car counters))) (cdr counters)))))

(define tt+
  (lambda (C)
    (lambda (minutes)
      (match C
        [(counter index tt et queue status)
         (struct-copy counter C [tt (+ tt minutes)])]))))


(define et+
  (lambda (C)
    (lambda (minutes)
      (match C
        [(counter index tt et queue status)
         (struct-copy counter C [et (+ et minutes)])]))))

(define change-status
  (lambda (C)
      (match C
        [(counter index tt et queue status)
         (struct-copy counter C [status 0])])))

(define (add-to-counter name items)
  (λ (C)
    (struct-copy counter C [tt (+(counter-tt C) items)] [et (if (queue-empty? (counter-queue C))
                                                                      (+ (counter-et C) items)
                                                                      (counter-et C))] [queue (enqueue (list* name items) (counter-queue C))])))

(define (min-helper f L min index)
  (cond
    [(null? L) (list* index min)]
    [(<(f (car L)) min) (min-helper f (cdr L) (f (car L)) (counter-index (car L)))]
    [else (min-helper f (cdr L) min index)]))
(define (trimmer L)
  (if (null? L)
      '()
      (if (= (counter-status (car L)) 1)
          (cons (car L) (trimmer (cdr L)))
          (trimmer (cdr L)))))


  
(define min-tt
  (lambda (counters)
    (min-helper counter-tt (trimmer counters) +inf.0 0)))
(define min-et
  (lambda (counters)
    (min-helper counter-et counters +inf.0 0)))

(define (remove-first-from-counter C) 
  (if (= (+ (queue-size-l (counter-queue C)) (queue-size-r (counter-queue C))) 1)
      (struct-copy counter C [tt 0] [et 0] [queue (dequeue (counter-queue C))])
      (struct-copy counter C [tt (tt-calculator (dequeue (counter-queue C)))] [et (cdr (top (dequeue (counter-queue C))))] [queue (dequeue (counter-queue C))])))
      
(define (tt-calculator queue)
  (if (queue-empty? queue)
      0
      (+ (cdr (top queue)) (tt-calculator (dequeue queue)))))

(define (pass-time-through-counter minutes)
  (λ (C)
    (if (<= (counter-tt C) minutes)
        (struct-copy counter C [tt 0] [et 0])
        (struct-copy counter C [tt (- (counter-tt C) minutes)] [et (- (counter-et C) minutes)]))))




; TODO
; Implementați funcția care simulează fluxul clienților pe la case.
; ATENȚIE: Față de etapa 3, apare un nou tip de cerere, așadar
; requests conține 5 tipuri de cereri (cele moștenite din etapa 3 plus una nouă):
;   - (<name> <n-items>) - persoana <name> trebuie așezată la coadă la o casă              (ca înainte)
;   - (delay <index> <minutes>) - casa <index> este întârziată cu <minutes> minute         (ca înainte)
;   - (ensure <average>) - cât timp tt-ul mediu al caselor este mai mare decât
;                          <average>, se adaugă case fără restricții (case slow)           (ca înainte)
;   - <x> - trec <x> minute de la ultima cerere, iar starea caselor se actualizează
;           corespunzător (cu efect asupra câmpurilor tt, et, queue)                       (ca înainte)
;   - (close <index>) - casa index este închisă                                            (   NOU!   )
; Sistemul trebuie să proceseze cele 5 tipuri de cereri în ordine, astfel:
; - persoanele vor fi distribuite la casele DESCHISE cu tt minim; nu se va întâmpla
;   niciodată ca o persoană să nu poată fi distribuită la nicio casă                       (mică modificare)
; - când o casă suferă o întârziere, tt-ul și et-ul ei cresc (chiar dacă nu are clienți);
;   nu aplicați vreun tratament special caselor închise                                    (ca înainte)
; - tt-ul mediu (ttmed) se calculează pentru toate casele DESCHISE, 
;   iar la nevoie veți adăuga case slow una câte una, până când ttmed <= <average>         (mică modificare)
; - când timpul prin sistem avansează cu <x> minute, tt-ul, et-ul și queue-ul tuturor 
;   caselor se actualizează pentru a reflecta trecerea timpului; dacă unul sau mai mulți 
;   clienți termină de stat la coadă, ieșirile lor sunt contorizate în ordine cronologică. (ca înainte)
; - când o casă se închide, ea nu mai primește clienți noi; clienții care erau deja acolo
;   avansează normal, până la ieșirea din supermarket                                    
; Rezultatul funcției serve va fi o pereche cu punct între:
; - lista sortată cronologic a clienților care au părăsit supermarketul:
;   - fiecare element din listă va avea forma (index_casă . nume)
;   - dacă mai mulți clienți ies simultan, sortați-i crescător după indexul casei
; - lista cozilor (de la case DESCHISE sau ÎNCHISE) care încă au clienți:
;   - fiecare element va avea forma (index_casă . coadă) (coada este de tip queue)
;   - lista este sortată după indexul casei
(define (serve requests fast-counters slow-counters)
  (serve-helper requests fast-counters slow-counters '() 0))

(define (serve-helper requests fast-counters slow-counters done t)
  (if (null? requests)
      (cons done (new-output (append fast-counters slow-counters)))
      (match (car requests)
        [(list 'close index)         (if (>= (length fast-counters) index)
                                         (serve-helper (cdr requests) (update change-status fast-counters index) slow-counters done t)
                                         (serve-helper (cdr requests) fast-counters (update change-status slow-counters index) done t))]
        [(list 'delay index minutes) (if (>= (length fast-counters) index)
                                         (serve-helper (cdr requests) (list-set fast-counters (- index 1) ((et+ ((tt+ (list-ref fast-counters (- index 1))) minutes)) minutes)) slow-counters done t)
                                         (serve-helper (cdr requests) fast-counters (list-set slow-counters (- (- index 1) (length fast-counters)) ((et+ ((tt+ (list-ref slow-counters (- (- index 1) (length fast-counters)))) minutes)) minutes)) done t))] 
        [(list 'ensure avg)         (if (> (med (append (lista fast-counters) (lista slow-counters))) avg)
                                        (serve-helper requests fast-counters (append slow-counters (list (empty-counter (+ (length (append fast-counters slow-counters)) 1)))) done t)
                                        (serve-helper (cdr requests) fast-counters slow-counters done t))]
        [(list name n-items)         (cond
                                       [(and (and (<= n-items ITEMS) (<= (car (min-tt (append fast-counters slow-counters))) (length fast-counters))) (= (counter-status (list-ref fast-counters (- (car (min-tt (append fast-counters slow-counters))) 1))) 1))
                                        (serve-helper (cdr requests) (list-set fast-counters (- (car (min-tt (append fast-counters slow-counters))) 1) ((add-to-counter name n-items) (list-ref fast-counters (- (car (min-tt (append fast-counters slow-counters))) 1)))) slow-counters done t)]
                                       [(and (and (<= n-items ITEMS) (> (car (min-tt (append fast-counters slow-counters))) (length fast-counters))) (= (counter-status (list-ref slow-counters (- (- (car (min-tt slow-counters)) 1) (length fast-counters)))) 1))
                                        (serve-helper (cdr requests) fast-counters (list-set slow-counters (- (- (car (min-tt slow-counters)) 1) (length fast-counters)) ((add-to-counter name n-items) (list-ref slow-counters (- (- (car (min-tt slow-counters)) 1) (length fast-counters))))) done t)]
                                       [else (if (= (counter-status (list-ref slow-counters (- (- (car (min-tt slow-counters)) 1) (length fast-counters)))) 1)
                                             (serve-helper (cdr requests) fast-counters (list-set slow-counters (- (- (car (min-tt slow-counters)) 1) (length fast-counters)) ((add-to-counter name n-items) (list-ref slow-counters (- (- (car (min-tt slow-counters)) 1) (length fast-counters))))) done t)
                                             (serve-helper (cdr requests) fast-counters slow-counters done t))])]
        [ x                          (let ((t (+ t x))  (done (append done (map cdr (sort-by-time (left (sort-by-et (append fast-counters slow-counters)) x x (+ t x)))))) (fast-counters (time fast-counters x x)) (slow-counters (time slow-counters x x)))
                                       (serve-helper (cdr requests) fast-counters slow-counters done t))])))

(define (new-output L)
  (if (null? L)
      '()
      (if (queue-empty? (counter-queue (car L)))
          (new-output (cdr L))
          (cons (cons (counter-index (car L)) (counter-queue (car L))) (new-output (cdr L))))))


(define (time L xi xf)
  (if (null? L)
      '()
      (if (queue-empty? (counter-queue (car L)))
          (if (<= xf (counter-tt (car L)))
              (cons ((pass-time-through-counter xf) (car L)) (time (cdr L) xi xi))
              (cons ((pass-time-through-counter (counter-tt (car L))) (car L)) (time (cdr L) xi xi)))
          (if (< xf (counter-et (car L)))
              (cons ((pass-time-through-counter xf) (car L)) (time (cdr L) xi xi))
              (let* ((xf (- xf (counter-et (car L)))) (new_counter (if (not (queue-empty? (counter-queue (car L))))
                                                                       (struct-copy counter (car L) [tt (- (counter-tt (car L)) (counter-et (car L)))] [queue (dequeue (counter-queue (car L)))])
                                                                       (struct-copy counter (car L) [tt 0] [et 0])))) (time (append (list (if (queue-empty? (counter-queue new_counter))
                                                                                                                                              (if (= (counter-status new_counter) 1)
                                                                                                                                                  (empty-counter (counter-index (car L)))
                                                                                                                                                  (change-status (empty-counter (counter-index (car L)))))
                                                                                                                                              (struct-copy counter new_counter [et (cdr (top (counter-queue new_counter)))]))) (cdr L)) xi xf))))))


(define (left L xi xf t)
  (if (null? L)
     '()
      (if (not (queue-empty? (counter-queue (car L))))
          (if (< xf (counter-et (car L)))
              (left (cdr L) xi xi t)
              (let ((new_counter (if (not (queue-empty? (counter-queue (car L))))
                                     (struct-copy counter (car L) [tt (- (counter-tt (car L)) (counter-et (car L)))] [queue (dequeue (counter-queue (car L)))])
                                     (struct-copy counter (car L) [tt 0] [et 0])))) (cons (list* (+ (- t xf) (counter-et (car L))) (counter-index (car L)) (car (top (counter-queue (car L))))) (left (append (list (if (queue-empty? (counter-queue new_counter))
                                                                                                                                                                                      (empty-counter (counter-index (car L)))
                                                                                                                                                                                      (struct-copy counter new_counter [et (cdr (top (counter-queue new_counter)))]))) (cdr L))  xi (- xf (counter-et (car L))) t))))
          (left (cdr L) xi xi t))))



(define (sort-by-et L)
  (sort L
        (lambda (e1 e2)
          (or (< (counter-et e1) (counter-et e2))
              (and (= (counter-et e1) (counter-et e2))
                   (< (counter-index e1) (counter-index e2)))))))

(define (sort-by-time L)
  (sort L
        (lambda (e1 e2)
          (or (< (car e1) (car e2))
              (and (= (car e1) (car e2))
                   (< (car (cdr e1)) (car (cdr e2))))))))
          
    

      
      

(define (med L)
  (/ (suma L) (length L)))



(define (suma L)
  (if (empty? L)
      0
      (+ (car L) (suma (cdr L))))) 

(define (lista L)
  (if (null? L)
      '()
      (if (= (counter-status (car L)) 1)
          (cons (counter-tt (car L)) (lista (cdr L)))
          (lista (cdr L)))))
        
