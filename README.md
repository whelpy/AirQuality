# AirQuality
air quality checker arduino

CO2
250-350ppm	Normal background concentration in outdoor ambient air

350-1,000ppm	Concentrations typical of occupied indoor spaces with good air exchange

1,000-2,000ppm	Complaints of drowsiness and poor air.

2,000-5,000 ppm	Headaches, sleepiness and stagnant, stale, stuffy air. Poor concentration, loss of attention, increased heart rate and slight nausea may also be present.

5,000	Workplace exposure limit (as 8-hour TWA) in most jurisdictions.

over 40,000 ppm	Exposure may lead to serious oxygen deprivation resulting in permanent brain damage, coma, even death.

255 0 0
248 7 0
241 14 0
234 21 0

each step red -7, green +7, blue is not needed

0 255 0

при этом 400 ppm (минимум датчика) считать за 255 зелёный и 0 красный, а 5000 ppm - максимум по санитарным нормам, считать за 0 зелёный, 255 красный. между ними 254 смешанных цвета (+1 к одному и -1 к другому каждый шаг)
т.е. каждые 18 ppm это изменение состояния цвета на 1 шаг

if (Nppm <400)
{
   Nppm = 400;
}

if (Nppm > 5000)
{
  Nppm = 5000;
}

K = (Nppm - 400) / 18 

Red = K

Green = 255 - K

// жёлтый самый яркий на среднем значении N, и угасает к крайним в обе стороны
if (N > 2300) // половина

{
  Yellow = K*2;
}
else

{
  Yellow = 255 - K*2;
}

