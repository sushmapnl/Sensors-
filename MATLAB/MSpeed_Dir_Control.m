clc;
clear all;
t = tcpip('141.219.121.105', 80);
fopen(t)



fprintf(t, '%d %d\n', [0 0]);


%fscanf(t, '%d', [1,inf]);

fclose(t); 