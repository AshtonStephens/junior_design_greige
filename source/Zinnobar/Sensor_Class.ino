int sensorPin = 5;
double threshold = 100;


class Sensor:

private:

int target_path;  // 0 = blue, 1 = red, 2 = yellow, 3 = black
//path values:
double v_blue, v_red, v_yellow, v_black;

public:

int sense()
{
  sensorRead = analogRead(sensorPin);
  if sensorRead <= v_blue + threshold && sensorRead >= v_blue - threshold
    return 0;
  else if sensorRead <= v_red + threshold && sensorRead >= v_red - threshold
    return 1;
  else if sensorRead <= v_yellow + threshold && sensorRead >= v_yellow - threshold
    return 2;
  else if sensorRead <= v_black + threshold && sensorRead >= v_black - threshold
    return 3;
}

void set_target_path(int path)
{
  target_path = path; 
}

void set_sensor_value(int path, double value)
{
  if path == 0
    v_blue = value;
  else if path == 1
    v_red = valuel;
  else if path == 2
    v_yellow = valuel;
  else if path == 3
    v_black = valuel
}










