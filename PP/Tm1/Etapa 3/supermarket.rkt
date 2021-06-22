#lang racket
(require racket/match)
(require "queue.rkt")
 (require racket/trace)
(provide (all-defined-out))

(define ITEMS 5)

;; ATENȚIE: Pentru această etapă a temei este necesar să implementați
;;          întâi TDA-ul queue în fișierul queue.rkt.
;; Reveniți la sarcinile din acest fișier după ce ați implementat tipul 
;; queue și ați verificat implementarea folosind checker-ul.


; Structura counter nu se modifică.
; Ceea ce se modifică este implementarea câmpului queue:
; - în loc de listă, acesta va fi o coadă (o structură de tip queue)
; - acest lucru nu este vizibil în definiția structurii counter,
;   ci în implementarea operațiilor acestui tip de date (tipul counter)
(define-struct counter (index tt et queue) #:transparent)


; TODO
; Actualizați funcțiile de mai jos astfel încât ele să folosească
; o structură de tip queue pentru reprezentarea cozii de persoane.
; Elementele cozii continuă să fie perechi (nume . nr_produse).
; Este esențial să respectați "bariera de abstractizare", adică să
; operați cu coada doar folosind interfața acestui TDA:
; - empty-queue
; - queue-empty?
; - enqueue
; - dequeue
; - top
; Obs: Doar câteva funcții vor necesita actualizări.
(define (empty-counter index)           ; testată de checker
  (make-counter index 0 0 empty-queue))

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
        [(counter index tt et queue)
         (struct-copy counter C [tt (+ tt minutes)])]))))


(define et+
  (lambda (C)
    (lambda (minutes)
      (match C
        [(counter index tt et queue)
         (struct-copy counter C [et (+ et minutes)])]))))

(define (add-to-counter name items)     ; testată de checker
  (λ (C)                                ; nu modificați felul în care funcția își primește argumentele
    (struct-copy counter C [tt (+(counter-tt C) items)] [et (if (queue-empty? (counter-queue C))
                                                                      (+ (counter-et C) items)
                                                                      (counter-et C))] [queue (enqueue (list* name items) (counter-queue C))])))

(define (min-helper f L min index)
  (cond
    [(null? L) (list* index min)]
    [(<(f (car L)) min) (min-helper f (cdr L) (f (car L)) (counter-index (car L)))]
    [else (min-helper f (cdr L) min index)]))

(define min-tt
  (lambda (counters)
    (min-helper counter-tt counters +inf.0 0)))
(define min-et
  (lambda (counters)
    (min-helper counter-et counters +inf.0 0)))

(define (remove-first-from-counter C)   ; testată de checker
  (if (= (+ (queue-size-l (counter-queue C)) (queue-size-r (counter-queue C))) 1)
      (struct-copy counter C [tt 0] [et 0] [queue (dequeue (counter-queue C))])
      (struct-copy counter C [tt (tt-calculator (dequeue (counter-queue C)))] [et (cdr (top (dequeue (counter-queue C))))] [queue (dequeue (counter-queue C))])))
      
(define (tt-calculator queue)
  (if (queue-empty? queue)
      0
      (+ (cdr (top queue)) (tt-calculator (dequeue queue)))))

; TODO
; Implementați o funcție care calculează starea unei case după un număr dat de minute.
; Funcția presupune, fără să verifice, că în acest timp nu a ieșit nimeni din coadă, 
; deci va avea efect doar asupra câmpurilor tt și et.
; (cu alte cuvinte, este responsabilitatea utilizatorului să nu apeleze această funcție
; cu minutes > timpul până la ieșirea primului client din coadă)
; Atenție: casele fără clienți nu trebuie să ajungă la timpi negativi!
(define (pass-time-through-counter minutes)
  (λ (C)
    (if (<= (counter-tt C) minutes)
        (struct-copy counter C [tt 0] [et 0])
        (struct-copy counter C [tt (- (counter-tt C) minutes)] [et (- (counter-et C) minutes)]))))

; TODO
; Implementați funcția care simulează fluxul clienților pe la case.
; ATENȚIE: Față de etapa 2, apar modificări în:
; - formatul listei de cereri (parametrul requests)
; - formatul rezultatului funcției (explicat mai jos)
; requests conține 4 tipuri de cereri (3 moștenite din etapa 2 plus una nouă):
;   - (<name> <n-items>) - persoana <name> trebuie așezată la coadă la o casă            (ca înainte)
;   - (delay <index> <minutes>) - casa <index> este întârziată cu <minutes> minute       (ca înainte)
;   - (ensure <average>) - cât timp tt-ul mediu al tuturor caselor este mai mare decât
;                          <average>, se adaugă case fără restricții (case slow)         (ca înainte)
;   - <x> - trec <x> minute de la ultima cerere, iar starea caselor se actualizează
;           corespunzător (cu efect asupra câmpurilor tt, et, queue)                     (   NOU!   )
; Obs: Au dispărut cererile de tip remove-first, pentru a lăsa loc unui mecanism mai 
; sofisticat de a scoate clienții din coadă (pe măsură ce trece timpul).
; Sistemul trebuie să proceseze cele 4 tipuri de cereri în ordine, astfel:
; - persoanele vor fi distribuite la casele cu tt minim (dintre casele la care au voie)  (ca înainte)
; - când o casă suferă o întârziere, tt-ul și et-ul ei cresc (chiar dacă nu are clienți) (ca înainte)
; - tt-ul mediu (ttmed) se calculează pentru toate casele (și cele fast, și cele slow), 
;   iar la nevoie veți adăuga case slow una câte una, până când ttmed <= <average>       (ca înainte)
; - când timpul prin sistem avansează cu <x> minute, tt-ul, et-ul și queue-ul tuturor 
;   caselor se actualizează pentru a reflecta trecerea timpului; dacă unul sau mai mulți 
;   clienți termină de stat la coadă, ieșirile lor sunt contorizate în ordine cronologică.
; Rezultatul funcției serve va fi o pereche cu punct între:
; - lista sortată cronologic a clienților care au părăsit supermarketul
;   - fiecare element din listă va avea forma (index_casă . nume)
;   - dacă mai mulți clienți ies simultan, sortați-i crescător după indexul casei
; - lista caselor în starea finală (ca rezultatul din etapele 1 și 2)
; Obs: Pentru a contoriza ieșirile din cozi, puteți să lucrați într-o funcție ajutătoare
; (cu un parametru în plus față de funcția serve), pe care serve doar o apelează.
(define (serve requests fast-counters slow-counters)
  (serve-helper requests fast-counters slow-counters '()))

(define (serve-helper requests fast-counters slow-counters done)
  (if (null? requests)
      (cons done (append fast-counters slow-counters))
      (match (car requests)
        [(list 'delay index minutes) (if (>= (length fast-counters) index)
                                         (serve-helper (cdr requests) (list-set fast-counters (- index 1) ((et+ ((tt+ (list-ref fast-counters (- index 1))) minutes)) minutes)) slow-counters done)
                                         (serve-helper (cdr requests) fast-counters (list-set slow-counters (- (- index 1) (length fast-counters)) ((et+ ((tt+ (list-ref slow-counters (- (- index 1) (length fast-counters)))) minutes)) minutes)) done))] 
        [(list 'ensure avg)         (if (> (med (append (lista fast-counters) (lista slow-counters))) avg)
                                        (serve-helper requests fast-counters (append slow-counters (list (empty-counter (+ (length (append fast-counters slow-counters)) 1)))) done)
                                        (serve-helper (cdr requests) fast-counters slow-counters done))]
        [(list name n-items)         (cond
                                       [(and (<= n-items ITEMS) (<= (car (min-tt (append fast-counters slow-counters))) (length fast-counters))) (serve-helper (cdr requests) (list-set fast-counters (- (car (min-tt (append fast-counters slow-counters))) 1) ((add-to-counter name n-items) (list-ref fast-counters (- (car (min-tt (append fast-counters slow-counters))) 1)))) slow-counters done)]
                                       [(and (<= n-items ITEMS) (> (car (min-tt (append fast-counters slow-counters))) (length fast-counters))) (serve-helper (cdr requests) fast-counters (list-set slow-counters (- (- (car (min-tt slow-counters)) 1) (length fast-counters)) ((add-to-counter name n-items) (list-ref slow-counters (- (- (car (min-tt slow-counters)) 1) (length fast-counters))))) done)]
                                       [else (serve-helper (cdr requests) fast-counters (list-set slow-counters (- (- (car (min-tt slow-counters)) 1) (length fast-counters)) ((add-to-counter name n-items) (list-ref slow-counters (- (- (car (min-tt slow-counters)) 1) (length fast-counters))))) done)])]
        [ x                          (let ((done (append done (left (sort-by-et (append fast-counters slow-counters)) x x))) (fast-counters (time fast-counters x x)) (slow-counters (time slow-counters x x)))
                                       (serve-helper (cdr requests) fast-counters slow-counters done))])))

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
                                                                                                                                              (empty-counter (counter-index (car L)))
                                                                                                                                              (struct-copy counter new_counter [et (cdr (top (counter-queue new_counter)))]))) (cdr L)) xi xf))))))

(define (left L xi xf) 
  (if (null? L)
      '()
      (if (not (queue-empty? (counter-queue (car L))))
          (if (< xf (counter-et (car L)))
              (left (cdr L) xi xi)
              (let ((new_counter (if (not (queue-empty? (counter-queue (car L))))
                                     (struct-copy counter (car L) [tt (- (counter-tt (car L)) (counter-et (car L)))] [queue (dequeue (counter-queue (car L)))])
                                     (struct-copy counter (car L) [tt 0] [et 0])))) (cons (list* (counter-index (car L)) (car (top (counter-queue (car L))))) (left (append (list (if (queue-empty? (counter-queue new_counter))
                                                                                                                                                                                      (empty-counter (counter-index (car L)))
                                                                                                                                                                                      (struct-copy counter new_counter [et (cdr (top (counter-queue new_counter)))]))) (cdr L))  xi (- xf (counter-et (car L)))))))
          (left (cdr L) xi xi))))
;(trace left)        
(define (sort-by-et L)
  (sort L
        (lambda (e1 e2)
          (or (< (counter-et e1) (counter-et e2))
              (and (= (counter-et e1) (counter-et e2))
                   (< (counter-index e1) (counter-index e2)))))))
          
    

      
      

(define (med L)
  (/ (suma L) (length L)))


(define (suma L)
  (if (empty? L)
      0
      (+ (car L) (suma (cdr L))))) 

(define (lista L)
  (if (null? L)
      '()
      (cons (counter-tt (car L)) (lista (cdr L)))))
        
