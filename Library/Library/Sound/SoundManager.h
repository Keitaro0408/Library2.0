﻿/**
* @file   SoundManager.h
* @brief  SoundManagerクラスのヘッダファイル
* @author kotani
*/
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include <windows.h>
#include <dsound.h>
#include <vector>
#include "..\Singleton\Singleton.h"

namespace Lib
{
	/**
	 * サウンドの再生をするクラス
	 *
	 * ここでサウンドのリソースを管理し実体は一つで良いのでシングルトンクラスにしている
	 */
	class SoundManager
	{
		friend Singleton<SoundManager>;
	public:
		/**
		* サウンドを操作するためのenum
		*/
		enum SOUND_OPERATION
		{
			SOUND_PLAY,		  //!< サウンドを再生する
			SOUND_STOP,		  //!< サウンドを停止する
			SOUND_LOOP,		  //!< サウンドをループ再生する
			SOUND_RESET,	  //!< サウンドをリセットする
			SOUND_STOP_RESET  //!< サウンドを停止してリセットする
		};

		/**
		 * SoundManagerクラスの初期化関数
		 * @param[in] _hWnd ウィンドウハンドル。コンストラクタ内で使う
		 * @return 成功したらtrue
		 */
		bool Initialize(HWND _hWnd);

		/**
		 * SoundManagerクラスの解放関数
		 */
		void Finalize();

		/**
		 * 音声の読み込み
		 * @param[in] _pFileName 読み込むファイルの名前
		 * @param[out] _pIndex データの格納先のインデックス
		 * @return 成功したらtrue
		 */
		bool LoadSound(LPSTR _pFileName, int* _pIndex);

		/**
		 * 音声の開放
		 * @param[in] _index 開放先のインデックス
		 */
		void ReleaseSound(int _index);

		/**
		 * サウンドの操作関数
		 * @param[in] _index 操作するサウンドの格納先のインデックス
		 * @param[in] _operation どのような操作をするか
		 */
		void SoundOperation(int _index, SOUND_OPERATION _operation);

		/**
		 * サウンドの音量調節
		 * @param[in] _index 操作するサウンドの格納先のインデックス
		 * @param[in] _ratio 素の音源から何%で再生するか?
		 */
		void SetSoundVolume(int _index, int _ratio);

		/**
		 * サウンドのバッファーを開放する
		 */
		inline void ClearResource()
		{
			m_pSound.clear();
			m_pSound.shrink_to_fit();
		}

	private:
		/**
		 * SoundManagerクラスのコンストラクタ
		 * @param[in] _hWnd 音声を鳴らすウィンドウのハンドル
		 */
		SoundManager();

		/**
		 * SoundManagerクラスのデストラクタ
		 */
		~SoundManager();

		/**
		 * waveファイル内のデータを読み出す関数
		 * @param[in] _pFileName 開くファイルの名前
		 * @param[out] _pWaveFormat 読み込んだwaveファイルのフォーマット
		 * @param[out] _pWaveData 読み込んだwaveファイルのデータ
		 * @param[out] _pWaveSize 読み込んだwaveファイルのサイズ
		 */
		bool ReadWave(LPSTR _pFileName, WAVEFORMATEX* _pWaveFormat, BYTE** _pWaveData, DWORD* _pWaveSize);

		IDirectSound8*					  m_pDSound8;
		HWND							  m_hWnd;
		std::vector<LPDIRECTSOUNDBUFFER8> m_pSound;
		static SoundManager*			  m_pSoundManager;

	};
}


#endif
