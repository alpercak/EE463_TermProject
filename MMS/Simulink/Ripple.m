t1 = 200;
t2 = 400;
T1 = 1.8;
T2 = 2.2;
figure(1);
hold on;
plot(out.RectifierCapacitor.Time(200000:400000)*1000, out.RectifierCapacitor.Data(200000:400000,1),'linewidth',2,"Color",'#FF0000');
title('Output Current Waveform vs. Time');
axis([t1 t2  T1 T2]);
%legend('Source Voltage','Source Current','Load Voltage','Load Current')
ylabel('Current(A)');
xlabel('time(ms)');
hold off;
figure(2);
hold on;
%plot(out.BuckInductor.Time(200000:400000)*1000, out.BuckInductor.Data(200000:400000,1),'linewidth',2,"Color",'#FF0000');
plot(out.BuckCapacitor.Time(200000:400000)*1000, out.BuckCapacitor.Data(200000:400000,1),'linewidth',2,"Color",'#00FF00');
title('Inductor Current Waveform vs. Time');
axis([t1 t2  T1 T2]);
%legend('Source Voltage','Source Current','Load Voltage','Load Current')
ylabel('Current(A)');
xlabel('time(ms)');
hold off;