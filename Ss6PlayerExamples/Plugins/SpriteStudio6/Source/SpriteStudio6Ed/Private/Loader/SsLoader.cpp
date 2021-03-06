﻿#include "SsLoader.h"

#include "Ss6Project.h"
#include "SsAnimePack.h"
#include "SsCellMap.h"
#include "SsArchiver.h"





USs6Project* FSsLoader::LoadSsProject(UObject* InParent, FName InName, EObjectFlags Flags, const uint8*& Buffer, size_t Size)
{
	XMLDocument xml;
	if( XML_SUCCESS != xml.Parse((const char*)Buffer, Size) )
	{
		return nullptr;
	}

	SsXmlIArchiver ar(&xml, "SpriteStudioProject");

	FString VersionStr;
	if(!ar.dc_attr("version", VersionStr) || !VersionStr.StartsWith("2."))
	{
		UE_LOG(LogSpriteStudioEd, Error, TEXT("Not Support SSPJ Version:%s"), *VersionStr);
		return nullptr;
	}

	USs6Project* Proj = NewObject<USs6Project>(InParent, InName, Flags);
	SerializeSsProject(*Proj, &ar);

	return Proj;
}

bool FSsLoader::LoadSsAnimePack(FSsAnimePack* AnimePack, const uint8*& Buffer, size_t Size)
{
	XMLDocument xml;
	if( XML_SUCCESS != xml.Parse((const char*)Buffer, Size) )
	{
		return false;
	}

	SsXmlIArchiver ar(&xml, "SpriteStudioAnimePack");
	SerializeSsAnimePack(*AnimePack, &ar);

	return true;
}

bool FSsLoader::LoadSsCellMap(FSsCellMap* CellMap, const uint8*& Buffer, size_t Size)
{
	XMLDocument xml;
	if( XML_SUCCESS != xml.Parse((const char*)Buffer, Size) )
	{
		return false;
	}

	SsXmlIArchiver ar(&xml, "SpriteStudioCellMap");
	SerializeSsCellMap(*CellMap, &ar);

	return true;
}

bool FSsLoader::LoadSsEffectFile(struct FSsEffectFile* EffectFile, const uint8*& Buffer, size_t Size)
{
	XMLDocument xml;
	if( XML_SUCCESS != xml.Parse((const char*)Buffer, Size) )
	{
		return false;
	}

	SsXmlIArchiver ar(&xml, "SpriteStudioEffect");
	SerializeSsEffectFile(*EffectFile, &ar);

	return true;
}

bool FSsLoader::LoadSsSequence(struct FSsSequencePack* SequencePack, const uint8* Buffer, size_t Size)
{
	XMLDocument xml;
	if( XML_SUCCESS != xml.Parse((const char*)Buffer, Size) )
	{
		return false;
	}

	SsXmlIArchiver ar(&xml, "SpriteStudioSequencePack");
	SerializeSsSequencePack(*SequencePack, &ar);

	return true;
}
