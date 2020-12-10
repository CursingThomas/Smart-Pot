class lichtSterkte
{
  public:
  lichtSterkte(int pin);
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
  int rawData;
};

