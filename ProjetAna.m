% Calcule du delais
% E[X^2] d'une Bounded Pareto  avec alpha = 2 (Wikipedia)
% \frac {2{H}^{2}{L}^{2}}{{H}^{2}-{L}^{2}}\ln {\frac {H}{L}}
H = 99;
L = 0.05;
alpha = 2;
EX2 = ((2*(H^2 )* L^2) /((H^2) - (L^2)))* log(H/L);
disp("Moment")

mu = 1./ B_pareto(alpha, L, H, 1);
tau = 0.1
disp(EX2)
delays = (1:1);
powers = (1:1)
for i = 1:7
    Tc  = (2^i)*10;
    for rho = 0.2:0.2:0.8
        lambda = rho/tau;
        ED = ((lambda * EX2) / (2 - 2*rho)) + ((1 - rho) * Tc / 2);
        delays(uint8(rho*5), i) = ED;
        powers(uint8(rho*5), i) = 1 - rho;
    end
    sleepCycle(i) = Tc;


end 


% Exporter pour LaTeX
for x = 2:2:8
A = [sleepCycle;delays(x/2, :)];

fileID = fopen(['output/delays-ana-0.', int2str(x), '.dat'],'w');
fprintf(fileID,'(%6.2f,%12.8f)',A);
fclose(fileID);

end



loglog(sleepCycle,delays(1,:), 'b')
hold on 
loglog(sleepCycle,delays(2,:), 'g')
hold on
loglog(sleepCycle,delays(3,:), 'r')
hold on
loglog(sleepCycle,delays(4,:), 'k')

legend('Ana rho = 0.2','Ana rho = 0.4', 'Ana rho = 0.6', 'Ana rho = 0.8', 'Location', 'southeast')
xlim([20,1280]);
xticks(sleepCycle);
ylim([1,1000]);
yticks([1, 10,100,1000]);
