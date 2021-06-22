clc; 
clear all; 
close all;
%Nume: Porumb Andrei-Cornel
%Grupa: 322CD
%Ex 1
%Task 1
s = tf('s');
H = 1/(0.7*s^2+0.1*s+0.3);
[puls, amort] = damp(H)
%Amortizarea este 0.1091
%Pulstatia naturala este 0.6547


%Task 2
B = isstable(H)
%Sistemul este stabil

S = stepinfo(H)
%Overshoot value: 70.8211
%Parametrul 0.1s afecteaza stabilitatea sitemului.

%Task 3



%Ex 2
A = [-51 15 8 ; 12 10 2 ; -8 12 -80];
B = [0.2 0 ; 0.4 1 ; 0 0];
C = [1 4 0 ; 0 15 0];
D = [0 0 ; 0 0];

H = ss(A,B,C,D)
%Task 1
%Asemanator cu laboratorul precedent, numarul intrarilor este dat de
%numarul de coloane ale matricei B, in acest caz 2, numarul starilor este
% dat de dimensiunile matricei A, in acest caz 3 stari, iar numarul
% iesirilor este dat de numarul de linii a matricei C, tot 2 in acest caz
%Deci sistemul nostru are 2 intrari, 3 stari si 2 iesiri.


%Task 2
isstable(H)
%Sistemul nu este stabil si nu se poate determina timpul tranzitoriu
%deoarece nu avem regim stationar

%Task 3
R = ctrb(A, B)
rank(R)
Q = obsv(A, C)
rank(Q)
%Sistemul este atat observabil cat si controlabil deoarece rank de R 
%si rank de Q sunt 3 (numarul de stari)

%Task 4
eig(A);

[n,n] = size(A);
[n,m] = size(B);
[p,n] = size(C);

Atilda = [A zeros(n,p);-C zeros(p,p)];
Btilda = [B; zeros(p,m)];
Ctilda = [zeros(p,n) eye(p)];

Fext = place(Atilda, Btilda, [-30 -31 -32 -33 -34]);
Fext = -Fext;
F = Fext(:,1:n);
Ftilda = Fext(:,n+1:n+p);
L = place(A',C',[-340 -350 -360]);
L = -L';
A1 = A+L*C+B*F;
A2 = B*Ftilda;
[l1,c1] = size(A1);
[l2,c2] = size(A2);

Ak = [A1 A2;zeros(c1+c2-l1,c1) zeros(c1+c2-l1,c2)];
Bk = [L; eye(size(L,2))];
Ck = Fext;
Dk = zeros(size(Ck,1),size(Bk,2));
K = ss(Ak,Bk,Ck,Dk)
T = ss(A,B,C,D)
H0 = feedback(series(K,T),eye(2))
step(H0,10)
%Pentru rezolvarea acestui punct am urmarit rezolvarea prezentata in
%indrumarul laboratorului. Valorile alese pentru F au fost alese random,
%adica am ales random un numar si am ales alte 4 numere din jurul acestuia.
%Pentru numerele din L am ales valori de cel putin 10 ori mai mari decat
%valorile din F. Valorile alese fiind deja destul de mici, stabilizxarea
%sistemului la 1 se petrece foarte rapid (aprox 0.5 secunde).