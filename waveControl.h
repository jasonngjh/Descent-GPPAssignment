#ifndef _WAVECONTROL_H
#define _WAVECONTROL_H

enum class WAVE_STATE{
	preWave,
	wave1,
	wave2,
	wave3,//bosswave
	pauseWave,
};

class WaveControl {
private:

	WAVE_STATE waveState;

public:

	WaveControl();
	~WaveControl();

	WAVE_STATE getWaveState() { return waveState; }
	void setWaveState(WAVE_STATE ws) { waveState = ws; }
};

#endif