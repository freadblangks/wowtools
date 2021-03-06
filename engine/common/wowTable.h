#pragma once

#include <stdint.h>
#include <vector>
#include <unordered_map>
#include <functional>

#include "wowDbFile.h"
#include <cassert>

class wowDatabase;

#define BUILD_INDEX_MAP(id2indexMap, field)		\
id2indexMap.reserve(RecordList.size());			\
for (uint32_t i = 0; i < (uint32_t)RecordList.size(); ++i)	\
{ id2indexMap[RecordList[i].##field] = i; }	

#define IMPLEMENT_RECORD_COMMON()	\
std::vector<SRecord>  RecordList;				\
std::unordered_map<uint32_t, uint32_t> Id2IndexMap;			\
std::function<void(const std::vector<VAR_T>& val)>   OnLoadItem;	\
bool hasKey() const { return !Id2IndexMap.empty(); }		\
const SRecord* getByID(uint32_t id) const		\
{							\
	auto itr = Id2IndexMap.find(id);			\
	if (itr == Id2IndexMap.end())			\
		return nullptr;					\
	return &RecordList[itr->second];			\
}

#define IMPLEMENT_RECORD_LOAD(name)			\
bool loadData(const wowDatabase* database)		\
{									\
	if (!g_IterateTableRecords(database, name, OnLoadItem))		\
		return false;				\
	BUILD_INDEX_MAP(Id2IndexMap, ID);			\
	return true;					\
}

bool g_IterateTableRecords(const wowDatabase* database, const char* tableName, const std::function<void(const std::vector<VAR_T>& val)>& callback);

/*
CharBaseSection
CharComponentTextureLayouts
CharComponentTextureSections
CharHairGeoSets
CharSections
CharacterFacialHairStyles
ChrClasses
ChrCustomization
ChrRaces
ComponentModelFileData
ComponentTextureFileData
CreatureDisplayInfo
CreatureDisplayInfoExtra
CreatureModelData
CreatureType
HelmetGeosetData
Item
ItemAppearance
ItemClass
ItemDisplayInfo
ItemDisplayInfoMaterialRes
ItemModifiedAppearance
ItemSet
ItemSparse
ItemSubClass
ModelFileData
Mount
MountXDisplay
NpcModelItemSlotDisplayInfo
ParticleColor
TextureFileData


*/

class CharBaseSectionTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		uint32_t LayoutResType;
		uint32_t VariationEnum;
		uint32_t ResolutionVariationEnum;
	};

	CharBaseSectionTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 4);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.LayoutResType = val[1].Get<uint32_t>();
			r.VariationEnum = val[2].Get<uint32_t>();
			r.ResolutionVariationEnum = val[3].Get<uint32_t>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("CharBaseSection");
};

class CharComponentTextureLayoutsTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		uint16_t Width;
		uint16_t Height;
	};

	CharComponentTextureLayoutsTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 3);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.Width = val[1].Get<uint16_t>();
			r.Height = val[2].Get<uint16_t>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("CharComponentTextureLayouts");
};

class CharComponentTextureSectionsTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		uint16_t LayoutID;
		uint16_t Section;
		uint16_t X;
		uint16_t Y;
		uint16_t Width;
		uint16_t Height;
	};

	CharComponentTextureSectionsTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 7);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.LayoutID = val[1].Get<uint16_t>();
			r.Section = val[2].Get<uint16_t>();
			r.X = val[3].Get<uint16_t>();
			r.Y = val[4].Get<uint16_t>();
			r.Width = val[5].Get<uint16_t>();
			r.Height = val[6].Get<uint16_t>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("CharComponentTextureSections");
};

class CharacterFacialHairStylesTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		uint32_t Geoset[5];
		uint16_t RaceID;
		uint16_t SexID;
		uint16_t VariationID;
	};

	CharacterFacialHairStylesTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 9);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			for (uint32_t i = 0; i < 5; ++i)
			{
				r.Geoset[i] = val[1 + i].Get<uint32_t>();
			}
			r.RaceID = val[6].Get<uint16_t>();
			r.SexID = val[7].Get<uint16_t>();
			r.VariationID = val[8].Get<uint16_t>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("CharacterFacialHairStyles");
};


class CharHairGeoSetsTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		uint16_t RaceID;
		uint16_t SexID;
		uint16_t VariationID;
		uint16_t GeoSetID;
		uint16_t ShowScalp;
		uint16_t VariationType;
		uint16_t GeoSetType;
		uint32_t ColorIndex;
		uint32_t CustomGeoFileDataID;
		uint32_t HdCustomGeoFileDataID;
	};

	CharHairGeoSetsTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 11);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.RaceID = val[1].Get<uint16_t>();
			r.SexID = val[2].Get<uint16_t>();
			r.VariationID = val[3].Get<uint16_t>();
			r.GeoSetID = val[4].Get<uint16_t>();
			r.ShowScalp = val[5].Get<uint16_t>();
			r.GeoSetType = val[6].Get<uint16_t>();
			r.VariationType = val[7].Get<uint16_t>();
			r.ColorIndex = val[8].Get<uint32_t>();
			r.CustomGeoFileDataID = val[9].Get<uint32_t>();
			r.HdCustomGeoFileDataID = val[10].Get<uint32_t>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("CharHairGeoSets");
};

class CharSectionsTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		uint16_t RaceID;
		uint16_t SexID;
		uint16_t SectionType;
		uint16_t VariationIndex;
		uint16_t ColorIndex;
		uint16_t Flags;
		uint32_t TextureName[3];
	};

	CharSectionsTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 10);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.RaceID = val[1].Get<uint16_t>();
			r.SexID = val[2].Get<uint16_t>();
			r.SectionType = val[3].Get<uint16_t>();
			r.VariationIndex = val[4].Get<uint16_t>();
			r.ColorIndex = val[5].Get<uint16_t>();
			r.Flags = val[6].Get<uint16_t>();
			for (uint32_t i = 0; i < 3; ++i)
			{
				r.TextureName[i] = val[7 + i].Get<uint32_t>();
			}
					
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("CharSections");
};

class ChrClassesTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		std::string Name;
	};

	ChrClassesTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 2);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.Name = val[1].Get<std::string>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("ChrClasses");
};

class ChrCustomizationTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		std::string Name;
		uint32_t Sex;
		uint32_t BaseSection;
		uint32_t UiCustomizationType;
		uint32_t Flags;
		int ComponentSection[3];
		uint32_t RaceId;
	};

	ChrCustomizationTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 10);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.Name = val[1].Get<std::string>();
			r.Sex = val[2].Get<uint32_t>();
			r.BaseSection = val[3].Get<uint32_t>();
			r.UiCustomizationType = val[4].Get<uint32_t>();
			r.Flags = val[5].Get<uint32_t>();
			for (uint32_t i = 0; i < 3; ++i)
			{
				r.ComponentSection[i] = val[6 + i].Get<int>();
			}
			r.RaceId = val[9].Get<uint32_t>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("ChrCustomization");
};

class ChrRacesTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		std::string ClientPrefix;
		uint32_t Flags;
		uint32_t MaleDisplayID;
		uint32_t FemaleDisplayID;
		uint32_t HighResMaleDisplayID;
		uint32_t HighResFemaleDisplayID;
		int BaseRaceID;
		uint16_t CharComponentTexLayoutID;
		uint16_t CharComponentTexLayoutHiResID;	
		int MaleModelFallbackRaceID;
		int MaleModelFallbackSex;
		int FemaleModelFallbackRaceID;
		int FemaleModelFallbackSex;
		int MaleTextureFallbackRaceID;
		int MaleTextureFallbackSex;
		int FemaleTextureFallbackRaceID;
		int FemaleTextureFallbackSex;
	};

	ChrRacesTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 18);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.ClientPrefix = val[1].Get<std::string>();
			r.Flags = val[2].Get<uint32_t>();
			r.MaleDisplayID = val[3].Get<uint32_t>();
			r.FemaleDisplayID = val[4].Get<uint32_t>();
			r.HighResMaleDisplayID = val[5].Get<uint32_t>();
			r.HighResFemaleDisplayID = val[6].Get<uint32_t>();
			r.BaseRaceID = val[7].Get<int>();
			r.CharComponentTexLayoutID = val[8].Get<uint16_t>();
			r.CharComponentTexLayoutHiResID = val[9].Get<uint16_t>();
			r.MaleModelFallbackRaceID = val[10].Get<int>();
			r.MaleModelFallbackSex = val[11].Get<int>();
			r.FemaleModelFallbackRaceID = val[12].Get<int>();
			r.FemaleModelFallbackSex = val[13].Get<int>();
			r.MaleTextureFallbackRaceID = val[14].Get<int>();
			r.MaleTextureFallbackSex = val[15].Get<int>();
			r.FemaleTextureFallbackRaceID = val[16].Get<int>();
			r.FemaleTextureFallbackSex = val[17].Get<int>();

			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("ChrRaces");
};

class ComponentModelFileDataTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		uint16_t GenderIndex;
		uint16_t ClassID;
		uint16_t RaceID;
		uint16_t PositionIndex;
	};

	ComponentModelFileDataTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 5);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.GenderIndex = val[1].Get<uint16_t>();
			r.ClassID = val[2].Get<uint16_t>();
			r.RaceID = val[3].Get<uint16_t>();
			r.PositionIndex = val[4].Get<uint16_t>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("ComponentModelFileData");
};

class ComponentTextureFileDataTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		uint16_t GenderIndex;
		uint16_t ClassID;
		uint16_t RaceID;
	};

	ComponentTextureFileDataTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 4);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.GenderIndex = val[1].Get<uint16_t>();
			r.ClassID = val[2].Get<uint16_t>();
			r.RaceID = val[3].Get<uint16_t>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("ComponentTextureFileData");
};

class CreatureDisplayInfoTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		uint16_t ModelID;
		uint32_t ExtendedDisplayInfoID;
		uint16_t ParticleColorID;
		uint32_t Texture[3];
	};

	CreatureDisplayInfoTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 7);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.ModelID = val[1].Get<uint16_t>();
			r.ExtendedDisplayInfoID = val[2].Get<uint32_t>();
			r.ParticleColorID = val[3].Get<uint16_t>();
			for (uint32_t i = 0; i < 3; ++i)
			{
				r.Texture[i] = val[4 + i].Get<uint32_t>();
			}
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("CreatureDisplayInfo");
};

class CreatureDisplayInfoExtraTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		uint16_t Skin;
		uint16_t Face;
		uint16_t HairStyle;
		uint16_t HairColor;
		uint16_t FacialHair;
	};

	CreatureDisplayInfoExtraTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 6);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.Skin = val[1].Get<uint16_t>();
			r.Face = val[2].Get<uint16_t>();
			r.HairStyle = val[3].Get<uint16_t>();
			r.HairColor = val[4].Get<uint16_t>();
			r.FacialHair = val[5].Get<uint16_t>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("CreatureDisplayInfoExtra");
};

class CreatureModelDataTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		uint32_t FileID;
	};

	CreatureModelDataTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 2);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.FileID = val[1].Get<uint32_t>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("CreatureModelData");
};

class CreatureTypeTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		std::string Name;
		uint16_t Flags;
	};

	CreatureTypeTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 3);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.Name = val[1].Get<std::string>();
			r.Flags = val[2].Get<uint16_t>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("CreatureType");
};

class HelmetGeosetDataTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		int RaceID;
		uint16_t GeosetGroup;
		uint32_t GeosetVisDataID;
	};

	HelmetGeosetDataTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 4);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.RaceID = val[1].Get<int>();
			r.GeosetGroup = val[2].Get<uint16_t>();
			r.GeosetVisDataID = val[3].Get<uint32_t>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("HelmetGeosetData");
};

class ItemTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		uint16_t Class;
		uint16_t SubClass;
		uint16_t Type;
		uint16_t Sheath;
	};

	ItemTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 5);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.Class = val[1].Get<uint16_t>();
			r.SubClass = val[2].Get<uint16_t>();
			r.Type = val[3].Get<uint16_t>();
			r.Sheath = val[4].Get<uint16_t>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("Item");
};

class ItemAppearanceTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		uint32_t ItemDisplayInfoID;
	};

	ItemAppearanceTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 2);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.ItemDisplayInfoID = val[1].Get<uint32_t>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("ItemAppearance");
};

class ItemClassTable
{
public:
	struct SRecord
	{
		uint32_t Col0;
		std::string Name;
		uint32_t ID;
	};

	ItemClassTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 3);
			SRecord r;
			r.Col0 = val[0].Get<uint32_t>();
			r.Name = val[1].Get<std::string>();
			r.ID = val[2].Get<uint32_t>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("ItemClass");
};

class ItemDisplayInfoTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		uint32_t ParticleColorID;
		int DisplayFlags;
		uint32_t Model[2];
		uint32_t TextureItemID[2];
		uint16_t GeosetGroup[6];
		uint16_t AttachmentGeosetGroup[6];
		uint32_t HelmetGeosetVis[2];
	};

	ItemDisplayInfoTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 21);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.ParticleColorID = val[1].Get<uint32_t>();
			r.DisplayFlags = val[2].Get<int>();
			for (uint32_t i = 0; i < 2; ++i)
			{
				r.Model[i] = val[3+i].Get<uint32_t>();
			}
			for (uint32_t i = 0; i < 2; ++i)
			{
				r.TextureItemID[i] = val[5+i].Get<uint32_t>();
			}			
			for (uint32_t i = 0; i < 6; ++i)
			{
				r.GeosetGroup[i] = val[7+i].Get<uint16_t>();
			}
			for (uint32_t i = 0; i < 6; ++i)
			{
				r.AttachmentGeosetGroup[i] = val[13 + i].Get<uint16_t>();
			}
			for (uint32_t i = 0; i < 2; ++i)
			{
				r.HelmetGeosetVis[i] = val[19+i].Get<uint32_t>();
			}
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("ItemDisplayInfo");
};

class ItemDisplayInfoMaterialResTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		uint32_t ItemDisplayInfoID;
		uint32_t TextureFileDataID;
	};

	ItemDisplayInfoMaterialResTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 3);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.ItemDisplayInfoID = val[1].Get<uint32_t>();
			r.TextureFileDataID = val[2].Get<uint32_t>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("ItemDisplayInfoMaterialRes");
};

class ItemModifiedAppearanceTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		uint32_t ItemID;
		uint16_t ItemAppearanceModifierID;
		uint32_t ItemAppearanceID;
		uint16_t ItemLevel;
	};

	ItemModifiedAppearanceTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 5);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.ItemID = val[1].Get<uint32_t>();
			r.ItemAppearanceModifierID = val[2].Get<uint16_t>();
			r.ItemAppearanceID = val[3].Get<uint32_t>();
			r.ItemLevel = val[4].Get<uint16_t>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("ItemModifiedAppearance");
};

class ItemSetTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		std::string Name;
		int Item[17];
	};

	ItemSetTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 19);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.Name = val[1].Get<std::string>();
			for (uint32_t i = 0; i < 17; ++i)
			{
				r.Item[i] = val[2 + i].Get<int>();
			}
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("ItemSet");
};

class ItemSparseTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		uint64_t AllowableRace;
		std::string Description;
		std::string DisplayLang3;
		std::string DisplayLang2;
		std::string DisplayLang1;
		std::string Name;
	};

	ItemSparseTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 7);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.AllowableRace = val[1].Get<uint64_t>();
			r.Description = val[2].Get<std::string>();
			r.DisplayLang3 = val[3].Get<std::string>();
			r.DisplayLang2 = val[4].Get<std::string>();
			r.DisplayLang1 = val[5].Get<std::string>();
			r.Name = val[6].Get<std::string>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("ItemSparse");
};

class ItemSubClassTable
{
public:
	struct SRecord
	{
		uint32_t Col0;
		std::string Name;
		std::string VerboseName;
		uint16_t ID;
		uint16_t SubClassID;
	};

	ItemSubClassTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 5);
			SRecord r;
			r.Col0 = val[0].Get<uint32_t>();
			r.Name = val[1].Get<std::string>();
			r.VerboseName = val[2].Get<std::string>();
			r.ID = val[3].Get<uint16_t>();
			r.SubClassID = val[4].Get<uint16_t>();		
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("ItemSubClass");
};

class ModelFileDataTable
{
public:
	struct SRecord
	{
		uint32_t ModelID;
		uint32_t ID;
	};

	ModelFileDataTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 2);
			SRecord r;
			r.ModelID = val[0].Get<uint32_t>();
			r.ID = val[1].Get<uint32_t>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("ModelFileData");
};

class MountTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		std::string Name;
	};

	MountTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 2);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.Name = val[1].Get<std::string>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("Mount");
};

class MountXDisplayTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		uint32_t MountID;
		uint32_t DisplayID;
	};

	MountXDisplayTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 3);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.MountID = val[1].Get<uint32_t>();
			r.DisplayID = val[2].Get<uint32_t>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("MountXDisplay");
};

class NpcModelItemSlotDisplayInfoTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		uint32_t ItemDisplayInfoID;
		uint16_t ItemType;
		uint32_t CreatureDisplayInfoExtraID;
	};

	NpcModelItemSlotDisplayInfoTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 4);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			r.ItemDisplayInfoID = val[1].Get<uint32_t>();
			r.ItemType = val[2].Get<uint16_t>();
			r.CreatureDisplayInfoExtraID = val[3].Get<uint32_t>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("NpcModelItemSlotDisplayInfo");
};

class ParticleColorTable
{
public:
	struct SRecord
	{
		uint32_t ID;
		int StartColor[3];
		int MidColor[3];
		int EndColor[3];
	};

	ParticleColorTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 10);
			SRecord r;
			r.ID = val[0].Get<uint32_t>();
			for (uint32_t i = 0; i < 3; ++i)
			{
				r.StartColor[i] = val[1+i].Get<int>();
			}
			for (uint32_t i = 0; i < 3; ++i)
			{
				r.MidColor[i] = val[4+i].Get<int>();
			}
			for (uint32_t i = 0; i < 3; ++i)
			{
				r.EndColor[i] = val[7+i].Get<int>();
			}
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("ParticleColor");
};

class TextureFileDataTable
{
public:
	struct SRecord
	{
		uint32_t TextureID;
		uint32_t ID;
	};

	TextureFileDataTable()
	{
		OnLoadItem = [this](const std::vector<VAR_T>& val)
		{
			assert(val.size() == 2);
			SRecord r;
			r.TextureID = val[0].Get<uint32_t>();
			r.ID = val[1].Get<uint32_t>();
			RecordList.emplace_back(r);
		};
	}

public:
	IMPLEMENT_RECORD_COMMON();

	IMPLEMENT_RECORD_LOAD("TextureFileData");
};

