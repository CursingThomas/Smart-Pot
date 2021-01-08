class LichtSterkte
{
  public:
  LichtSterkte(int pin, String sensorNaam);
  int pullData();
  int processData();
  void printRawData();
  void printProcessedData();
  String dataToString();
  String clearString();


  private:
  int pin;
  int processedData;
  String strProcessedData;
  String sensorNaam;
  int rawData;
};

