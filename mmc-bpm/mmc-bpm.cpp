// mmc-bpm.cpp: 定义应用程序的入口点。
//

#include <stdio.h>
#include <iostream>
// 使用aubio库(没打错 就是aubio)
#include "aubio.h"

// #include "mmc-bpm.h"

using namespace std;

int main()
{
	// 加载音频文件
	aubio_source_t* source = new_aubio_source("input.wav",0,0);
	
	// 参数
	uint_t samplerate = aubio_source_get_samplerate(source);
	uint_t hop_size = 256;
	uint_t buffer_size = hop_size *4;
	fvec_t* in = new_fvec(hop_size, 1);

	// 创建tempo对象
	aubio_tempo_t* tempo = new_aubio_tempo("default", buffer_size, hop_size, samplerate);

	// 读取数据计算BPM
	int i = 0;
	do {
		aubio_source_do(source, in, &i);
		aubio_tempo_do(tempo, in, &i);
	} while (i == hop_size);

	// 输出计算结果
	cout << "BPM的计算结果为: " << bpm << endl;

	// 释放资源
	del_aubio_tempo(tempo);
	del_fvec(in);
	del_aubio_source(source);
	return 0;
}

