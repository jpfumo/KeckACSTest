%Matlab script to input file from ACS testset
clear all
%filestring = 'ACS';
filestring = 'F:\ACS0000.txt';
fileID = fopen(filestring,'r');
A = fread(fileID,[2,inf],'int16');

B = A(1,:);
B = B.*0.000004; % 4uA/bit with 1ohm Sense Resistor

C = A(2,:);
figure
subplot(2,1,1);
plot(C,'b');
title('ACS APC POSITION');
xlabel('steps');
ylabel('APC COUNT');

subplot(2,1,2);
plot(B,'g');
title('ACS MOTOR CURRENT');
ylabel('Motor Current, Amps');
xlabel('steps');

figure
D = B; 
for L = 1:length(A)  
    D(L) = D(L)-L;
end
    D(1) = 0;
plot(D,"r");
title('ACS APC POSITION SLOPE REMOVED');
xlabel('steps');
ylabel('APC COUNT');






    
   
