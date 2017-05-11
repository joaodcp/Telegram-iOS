﻿#pragma once

#include "../../VoIPController.h"
#include "../../VoIPServerConfig.h"

namespace libtgvoip{
	public ref class Endpoint sealed{
	public:
		property int64 id;
		property uint16 port;
		property Platform::String^ ipv4;
		property Platform::String^ ipv6;
		property Platform::Array<uint8>^ peerTag;
	};

	public interface class IStateCallback{
		void OnCallStateChanged(int newState);
	};

    public ref class VoIPControllerWrapper sealed{
    public:
        VoIPControllerWrapper();
		void Start();
		void Connect();
		void SetPublicEndpoints(Windows::Foundation::Collections::IIterable<Endpoint^>^ endpoints, bool allowP2P);
		void SetNetworkType(int type);
		void SetStateCallback(IStateCallback^ callback);
		void SetMicMute(bool mute);
		void SetEncryptionKey(const Platform::Array<uint8>^ key, bool isOutgoing);
		Platform::String^ GetDebugString();
		Platform::String^ GetDebugLog();
		int GetLastError();
		static Platform::String^ GetVersion();
		//static Platform::String^ TestAesIge();
	private:
		~VoIPControllerWrapper();
		static void OnStateChanged(tgvoip::VoIPController* c, int state);
		void OnStateChangedInternal(int state);
		tgvoip::VoIPController* controller;
		IStateCallback^ stateCallback;
    };

	ref class MicrosoftCryptoImpl{
	public:
		static void AesIgeEncrypt(uint8_t* in, uint8_t* out, size_t len, uint8_t* key, uint8_t* iv);
		static void AesIgeDecrypt(uint8_t* in, uint8_t* out, size_t len, uint8_t* key, uint8_t* iv);
		static void SHA1(uint8_t* msg, size_t len, uint8_t* out);
		static void SHA256(uint8_t* msg, size_t len, uint8_t* out);
		static void RandBytes(uint8_t* buffer, size_t len);
		static void Init();
	private:
		static inline void XorInt128(uint8_t* a, uint8_t* b, uint8_t* out);
		/*static Windows::Security::Cryptography::Core::CryptographicHash^ sha1Hash;
		static Windows::Security::Cryptography::Core::CryptographicHash^ sha256Hash;*/
		static Windows::Security::Cryptography::Core::HashAlgorithmProvider^ sha1Provider;
		static Windows::Security::Cryptography::Core::HashAlgorithmProvider^ sha256Provider;
		static Windows::Security::Cryptography::Core::SymmetricKeyAlgorithmProvider^ aesKeyProvider;
	};
}