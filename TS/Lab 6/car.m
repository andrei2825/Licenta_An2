function [] = car(A, B, C, D)
    sys = ss(A,B,C,D);
    E = B;
    t = 0:1:25;
    u1 = 100;
    u2 = 24;
    u = [u1 u2];
    U = repmat(u, numel(t), 1);
    y = lsim(sys, U, t);
    figure
    subplot(3, 1, 1)
    plot(y(:,1))
    title('Distanta(km)')
    xlabel('Time(s)')
    ylabel('Dist(km)')
    subplot(3, 1, 2)
    plot(y(:,2))
    title('Viteza(km/h)')
    xlabel('Time(s)')
    ylabel('Viteza(km/h)')
    subplot(3, 1, 3)
    plot(y(:,3))
    title('Temperatura(C)')
    xlabel('Time(s)')
    ylabel('Temp(c)')
    y
    %Task 1: Dupa 25 de secunde, masina s-a deplasat 0.6389km
    %        Se atinge o temperatura de aproximativ 24 de grade (23.917
    %        dupa aproximativ 17 secunde. Nu se va atinge temperatura
    %        exacta de 24 de grade incele 25 de secunde date.
    
    R = ctrb(A, B)
    rank(R)
    
    Q = obsv(A, C)
    rank(Q)
    
    %Task 2: Sistemul este atat observabil cat si controlabil deoarece
    %        rank de R si rank de Q sunt 3 (numarul de stari)
    
    B = [0 0; 0 0; 0 0.33]
    
    
    sys = ss(A,B,C,D);
    t = 0:1:25;
    u1 = 100;
    u2 = 24;
    u = [u1 u2];
    U = repmat(u, numel(t), 1);
    y = lsim(sys, U, t);
    figure
    subplot(3, 1, 1)
    plot(y(:,1))
    title('Distanta(km)')
    xlabel('Time(s)')
    ylabel('Dist(km)')
    subplot(3, 1, 2)
    plot(y(:,2))
    title('Viteza(km/h)')
    xlabel('Time(s)')
    ylabel('Viteza(km/h)')
    subplot(3, 1, 3)
    plot(y(:,3))
    title('Temperatura(C)')
    xlabel('Time(s)')
    ylabel('Temp(c)')
    
    
    
    R = ctrb(A, B)
    rank(R)
    
    Q = obsv(A, C)
    rank(Q)
    
    %Task 3: In urma modificarii lui B, masina nu mai porneste ( nu creste
    %        viteza iar masina ramane pe loc).
    %        Sistemul ramane observabil ( Q = 3 ) dar nu mai este
    %        controlabil ( R este 1 ).
    
    B = E;
    C = [1 0 0; 0 1 0; 0 0 0]
    
    
    
    sys = ss(A,B,C,D);
    t = 0:1:25;
    u1 = 100;
    u2 = 24;
    u = [u1 u2];
    U = repmat(u, numel(t), 1);
    y = lsim(sys, U, t);
    figure
    subplot(3, 1, 1)
    plot(y(:,1))
    title('Distanta(km)')
    xlabel('Time(s)')
    ylabel('Dist(km)')
    subplot(3, 1, 2)
    plot(y(:,2))
    title('Viteza(km/h)')
    xlabel('Time(s)')
    ylabel('Viteza(km/h)')
    subplot(3, 1, 3)
    plot(y(:,3))
    title('Temperatura(C)')
    xlabel('Time(s)')
    ylabel('Temp(c)')
    
    
    
    R = ctrb(A, B)
    rank(R)
    
    Q = obsv(A, C)
    rank(Q)
    
    %Task 4: In ruma modificarii matricei C, temperatura nu se mai
    %        modifica, sistemul ramane controlabil (R = 3) dar nu mai este
    %        observabil (Q este 2)
    
end

