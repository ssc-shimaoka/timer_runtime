class Model
{
    public:
        int appMode;
        int blockNumber;
        int blockSurvivalTime;
        int timerStatus;
        
        int setTime;
        long operatingTime;
        long startTime;
        int elapsedTime;
        
        int updateInterval;
        
        long pauseStartTime;
        long pauseEndTime;
        long pauseTotalTime;
        
    public:
        Model();
        void init();
};

Model::Model()
{
}

void Model::init()
{
    appMode = 0;
    blockNumber = 6;
    blockSurvivalTime = 30;
    timerStatus = 0;
        
    setTime = 0;
    operatingTime = 0;
    startTime = 0;
    elapsedTime = 0;
        
    updateInterval = 1000;
        
    pauseStartTime = 0;
    pauseEndTime = 0;
    pauseTotalTime = 0;
}

