%% Setup TCP connection
t = tcpip('141.219.121.105', 80);
fopen(t)

%% Send an integer
fprintf(t, "%d", 22)

%% Receive an integer
fscanf(t, "%d")

%% Close connection
fclose(t)