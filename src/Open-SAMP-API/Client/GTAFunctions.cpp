#include "GTAFunctions.hpp"
#include "MemoryFunctions.hpp"
#include <Shared/PipeMessages.hpp>

EXPORT bool Client::GTAFunctions::IsMenuOpen()
{
	BYTE bOpen;
	MemoryFunctions::ReadMemory(0xB6B964, 1, (char *)&bOpen);
	return bOpen != 0;
}

EXPORT bool Client::GTAFunctions::WorldToScreen(float x, float y, float z, float& screenX, float& screenY)
{
	SERVER_CHECK(0)

	Utils::Serializer serializerIn, serializerOut;

	serializerIn << Shared::PipeMessages::WorldToScreen << x << y << z;

	if (Utils::PipeClient(serializerIn, serializerOut).success())
	{
		bool bRes = false;
		serializerOut >> bRes >> screenX >> screenY;
		return bRes;
	}

	return 0;
}