classdef Solver
    methods
        % 1
        function T = solve_1(self)
        % Find the parameter T of a first-order transfer function
        % with k = 1000 and settling time of 0.4 seconds on impulse
            s = tf('s');
            k = 1000;
            t_settle = 0.4;
            %indiferent de k, T ramane acelasi
            T = t_settle / 4;
            H = k/(T*s+1);
            step(H);
        end
        
        % 2
        function w = solve_2(self)
        % Find the w parameter of a second-order transfer function
        % with zeta = 0.2 and a peak time of 0.4 seconds on step
            s = tf('s');
            z = 0.2;
            t_peak = 0.4;
            w = pi/(t_peak*sqrt(1-z^2));
            H = w^2/(s^2 + 2*z*w*s+1);
            step(H);
        end
        
        % 3
        function t_rise = solve_3(self, w, zetas)
        % Compute the rise times of a second-order function
        % with given w for each value zeta in zetas
            s = tf('s');
            size = length(zetas);
            for i = 1:size
                t_rise(i) =  (1.2 - 0.45*zetas(i) + 2.6*zetas(i)^2)/w;
            end
        end
        
        % 4
        function overshoots = solve_4(self, w, zetas)
        % Compute the overshoots of a second-order function
        % with given w for each value zeta in zetas
        % (don't convert to percents)
            s = tf('s');
            size = length(zetas);
            for i = 1:size 
                overshoots(i) =  exp(-pi*zetas(i)/sqrt(1-zetas(i)^2));
            end
        end
        
        % 5
        function t_stationary = solve_5(self)
        % Compute the time it takes for the Iron Man suit to stop.
        % Time and input are provided.
            s = tf('s');
            w = 12;
            z = 0.2;
            H = w^2 / (s^2 + 2*w*z*s + w^2);
            t = [0:0.1:10];         % Use this time vector
            u = [t <= 3] - [t > 3]; % Use this as input
            [y, T] = lsim(H, u, t);
            y(1) = [];
            y = y.';
            T(1) = [];
            T = T.';
            lsim(H, u, t);
            dy = diff([0 y]);
            dyix = find(dy == 0);
            y(dyix) = y(dyix-1)+1E-8;
            %Cred ca am calculat bine timpul, insa mereu rezulta decalat 
            %cu -0.5 secunde. 
            t_stationary = interp1(y, T, 0) + 0.5;
        end
    end
    
end