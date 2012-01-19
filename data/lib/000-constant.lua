NORTH = 0
EAST = 1
SOUTH = 2
WEST = 3
SOUTHWEST = 4
SOUTHEAST = 5
NORTHWEST = 6
NORTHEAST = 7

COMBAT_FORMULA_UNDEFINED = 0
COMBAT_FORMULA_LEVELMAGIC = 1
COMBAT_FORMULA_SKILL = 2
COMBAT_FORMULA_DAMAGE = 3

CONDITION_PARAM_OWNER = 1
CONDITION_PARAM_TICKS = 2
CONDITION_PARAM_OUTFIT = 3
CONDITION_PARAM_HEALTHGAIN = 4
CONDITION_PARAM_HEALTHTICKS = 5
CONDITION_PARAM_MANAGAIN = 6
CONDITION_PARAM_MANATICKS = 7
CONDITION_PARAM_DELAYED = 8
CONDITION_PARAM_SPEED = 9
CONDITION_PARAM_LIGHT_LEVEL = 10
CONDITION_PARAM_LIGHT_COLOR = 11
CONDITION_PARAM_SOULGAIN = 12
CONDITION_PARAM_SOULTICKS = 13
CONDITION_PARAM_MINVALUE = 14
CONDITION_PARAM_MAXVALUE = 15
CONDITION_PARAM_STARTVALUE = 16
CONDITION_PARAM_TICKINTERVAL = 17
CONDITION_PARAM_FORCEUPDATE = 18
CONDITION_PARAM_SKILL_MELEE = 19
CONDITION_PARAM_SKILL_FIST = 20
CONDITION_PARAM_SKILL_CLUB = 21
CONDITION_PARAM_SKILL_SWORD = 22
CONDITION_PARAM_SKILL_AXE = 23
CONDITION_PARAM_SKILL_DISTANCE = 24
CONDITION_PARAM_SKILL_SHIELD = 25
CONDITION_PARAM_SKILL_FISHING = 26
CONDITION_PARAM_STAT_MAXHEALTH = 27
CONDITION_PARAM_STAT_MAXMANA = 28
CONDITION_PARAM_STAT_SOUL = 29
CONDITION_PARAM_STAT_MAGICLEVEL = 30
CONDITION_PARAM_STAT_MAXHEALTHPERCENT = 31
CONDITION_PARAM_STAT_MAXMANAPERCENT = 32
CONDITION_PARAM_STAT_SOULPERCENT = 33
CONDITION_PARAM_STAT_MAGICLEVELPERCENT = 34
CONDITION_PARAM_SKILL_MELEEPERCENT = 35
CONDITION_PARAM_SKILL_FISTPERCENT = 36
CONDITION_PARAM_SKILL_CLUBPERCENT = 37
CONDITION_PARAM_SKILL_SWORDPERCENT = 38
CONDITION_PARAM_SKILL_AXEPERCENT = 39
CONDITION_PARAM_SKILL_DISTANCEPERCENT = 40
CONDITION_PARAM_SKILL_SHIELDPERCENT = 41
CONDITION_PARAM_SKILL_FISHINGPERCENT = 42
CONDITION_PARAM_PERIODICDAMAGE = 43
CONDITION_PARAM_BUFF = 44
CONDITION_PARAM_SUBID = 45
CONDITION_PARAM_FIELD = 46

COMBAT_PARAM_TYPE = 1
COMBAT_PARAM_EFFECT = 2
COMBAT_PARAM_DISTANCEEFFECT = 3
COMBAT_PARAM_BLOCKSHIELD = 4
COMBAT_PARAM_BLOCKARMOR = 5
COMBAT_PARAM_TARGETCASTERORTOPMOST = 6
COMBAT_PARAM_CREATEITEM = 7
COMBAT_PARAM_AGGRESSIVE = 8
COMBAT_PARAM_DISPEL = 9
COMBAT_PARAM_USECHARGES = 10
COMBAT_PARAM_TARGETPLAYERSORSUMMONS = 11
COMBAT_PARAM_DIFFERENTAREADAMAGE = 12
COMBAT_PARAM_HITEFFECT = 13
COMBAT_PARAM_HITCOLOR = 14

CALLBACK_PARAM_LEVELMAGICVALUE = 1
CALLBACK_PARAM_SKILLVALUE = 2
CALLBACK_PARAM_TARGETTILE = 3
CALLBACK_PARAM_TARGETCREATURE = 4

COMBAT_NONE = 0
COMBAT_PHYSICALDAMAGE = 1
COMBAT_ENERGYDAMAGE = 2
COMBAT_EARTHDAMAGE = 4
COMBAT_POISONDAMAGE = 4
COMBAT_FIREDAMAGE = 8
COMBAT_UNDEFINEDDAMAGE = 16
COMBAT_LIFEDRAIN = 32
COMBAT_MANADRAIN = 64
COMBAT_HEALING = 128
COMBAT_DROWNDAMAGE = 256
COMBAT_ICEDAMAGE = 512
COMBAT_HOLYDAMAGE = 1024
COMBAT_DEATHDAMAGE = 2048

CONDITION_NONE = 0
CONDITION_POISON = 1
CONDITION_FIRE = 2
CONDITION_ENERGY = 4
CONDITION_BLEEDING = 8
CONDITION_HASTE = 16
CONDITION_PARALYZE = 32
CONDITION_OUTFIT = 64
CONDITION_INVISIBLE = 128
CONDITION_LIGHT = 256
CONDITION_MANASHIELD = 512
CONDITION_INFIGHT = 1024
CONDITION_DRUNK = 2048
CONDITION_EXHAUST = 4096
CONDITION_FOOD = 8192
CONDITION_REGENERATION = 8192
CONDITION_SOUL = 16384
CONDITION_DROWN = 32768
CONDITION_MUTED = 65536
CONDITION_ATTRIBUTES = 131072
CONDITION_FREEZING = 262144
CONDITION_DAZZLED = 524288
CONDITION_CURSED = 1048576
CONDITION_PACIFIED = 2097152
CONDITION_GAMEMASTER = 4194304
CONDITION_HUNTING = 8388608
CONDITION_SPELLCOOLDOWN = 16777216

CONDITIONID_DEFAULT = -1
CONDITIONID_COMBAT = 0
CONDITIONID_HEAD = 1
CONDITIONID_NECKLACE = 2
CONDITIONID_BACKPACK = 3
CONDITIONID_ARMOR = 4
CONDITIONID_RIGHT = 5
CONDITIONID_LEFT = 6
CONDITIONID_LEGS = 7
CONDITIONID_FEET = 8
CONDITIONID_RING = 9
CONDITIONID_AMMO = 10
CONDITIONID_OUTFIT = 11

EXHAUST_OTHER = 0
EXHAUST_SPELLGROUP_NONE = 1
EXHAUST_SPELLGROUP_ATTACK = 2
EXHAUST_SPELLGROUP_HEALING = 3
EXHAUST_SPELLGROUP_SUPPORT = 4
EXHAUST_SPELLGROUP_SPECIAL = 5
EXHAUST_MELEE = 6

MUTED_BUFFER = 0
MUTED_YELL = 1
MUTED_MAIL = 2
MUTED_TRADE = 3
MUTED_TRADE_ROOK = 4

GAMEMASTER_INVISIBLE = 0
GAMEMASTER_IGNORE = 1
GAMEMASTER_TELEPORT = 2

CONST_SLOT_FIRST = 1
CONST_SLOT_HEAD = CONST_SLOT_FIRST
CONST_SLOT_NECKLACE = 2
CONST_SLOT_BACKPACK = 3
CONST_SLOT_ARMOR = 4
CONST_SLOT_RIGHT = 5
CONST_SLOT_LEFT = 6
CONST_SLOT_LEGS = 7
CONST_SLOT_FEET = 8
CONST_SLOT_RING = 9
CONST_SLOT_AMMO = 10
CONST_SLOT_LAST = CONST_SLOT_AMMO

CONST_ME_DRAWBLOOD = 0
CONST_ME_LOSEENERGY = 1
CONST_ME_POFF = 2
CONST_ME_BLOCKHIT = 3
CONST_ME_EXPLOSIONAREA = 4
CONST_ME_EXPLOSIONHIT = 5
CONST_ME_FIREAREA = 6
CONST_ME_YELLOW_RINGS = 7
CONST_ME_GREEN_RINGS = 8
CONST_ME_HITAREA = 9
CONST_ME_TELEPORT = 10
CONST_ME_ENERGYHIT = 11
CONST_ME_MAGIC_BLUE = 12
CONST_ME_MAGIC_RED = 13
CONST_ME_MAGIC_GREEN = 14
CONST_ME_HITBYFIRE = 15
CONST_ME_HITBYPOISON = 16
CONST_ME_MORTAREA = 17
CONST_ME_SOUND_GREEN = 18
CONST_ME_SOUND_RED = 19
CONST_ME_POISONAREA = 20
CONST_ME_SOUND_YELLOW = 21
CONST_ME_SOUND_PURPLE = 22
CONST_ME_SOUND_BLUE = 23
CONST_ME_SOUND_WHITE = 24
CONST_ME_BUBBLES = 25
CONST_ME_CRAPS = 26
CONST_ME_GIFT_WRAPS = 27
CONST_ME_FIREWORK_YELLOW = 28
CONST_ME_FIREWORK_RED = 29
CONST_ME_FIREWORK_BLUE = 30
CONST_ME_STUN = 31
CONST_ME_SLEEP = 32
CONST_ME_WATERCREATURE = 33
CONST_ME_GROUNDSHAKER = 34
CONST_ME_HEARTS = 35
CONST_ME_FIREATTACK = 36
CONST_ME_ENERGYAREA = 37
CONST_ME_SMALLCLOUDS = 38
CONST_ME_HOLYDAMAGE = 39
CONST_ME_BIGCLOUDS = 40
CONST_ME_ICEAREA = 41
CONST_ME_ICETORNADO = 42
CONST_ME_ICEATTACK = 43
CONST_ME_STONES = 44
CONST_ME_SMALLPLANTS = 45
CONST_ME_CARNIPHILA = 46
CONST_ME_PURPLEENERGY = 47
CONST_ME_YELLOWENERGY = 48
CONST_ME_HOLYAREA = 49
CONST_ME_BIGPLANTS = 50
CONST_ME_CAKE = 51
CONST_ME_GIANTICE = 52
CONST_ME_WATERSPLASH = 53
CONST_ME_PLANTATTACK = 54
CONST_ME_TUTORIALARROW = 55
CONST_ME_TUTORIALSQUARE = 56
CONST_ME_MIRRORHORIZONTAL = 57
CONST_ME_MIRRORVERTICAL = 58
CONST_ME_SKULLHORIZONTAL = 59
CONST_ME_SKULLVERTICAL = 60
CONST_ME_ASSASSIN = 61
CONST_ME_STEPSHORIZONTAL = 62
CONST_ME_BLOODYSTEPS = 63
CONST_ME_STEPSVERTICAL = 64
CONST_ME_YALAHARIGHOST = 65
CONST_ME_BATS = 66
CONST_ME_SMOKE = 67
CONST_ME_INSECTS = 68
CONST_ME_DRAGONHEAD = 69
CONST_ME_ORCSHAMAN = 70
CONST_ME_ORCSHAMAN_FIRE = 71
CONST_ME_THUNDER = 72
CONST_ME_FERUMBRAS = 73
CONST_ME_CONFETTIHORIZONTAL = 74
CONST_ME_CONFETTIVERTICAL = 75
CONST_ME_NONE = 255
CONST_ME_LAST = CONST_ME_CONFETTIVERTICAL

CONST_ANI_SPEAR = 0
CONST_ANI_BOLT = 1
CONST_ANI_ARROW = 2
CONST_ANI_FIRE = 3
CONST_ANI_ENERGY = 4
CONST_ANI_POISONARROW = 5
CONST_ANI_BURSTARROW = 6
CONST_ANI_THROWINGSTAR = 7
CONST_ANI_THROWINGKNIFE = 8
CONST_ANI_SMALLSTONE = 9
CONST_ANI_DEATH = 10
CONST_ANI_LARGEROCK = 11
CONST_ANI_SNOWBALL = 12
CONST_ANI_POWERBOLT = 13
CONST_ANI_POISON = 14
CONST_ANI_INFERNALBOLT = 15
CONST_ANI_HUNTINGSPEAR = 16
CONST_ANI_ENCHANTEDSPEAR = 17
CONST_ANI_REDSTAR = 18
CONST_ANI_GREENSTAR = 19
CONST_ANI_ROYALSPEAR = 20
CONST_ANI_SNIPERARROW = 21
CONST_ANI_ONYXARROW = 22
CONST_ANI_PIERCINGBOLT = 23
CONST_ANI_WHIRLWINDSWORD = 24
CONST_ANI_WHIRLWINDAXE = 25
CONST_ANI_WHIRLWINDCLUB = 26
CONST_ANI_ETHEREALSPEAR = 27
CONST_ANI_ICE = 28
CONST_ANI_EARTH = 29
CONST_ANI_HOLY = 30
CONST_ANI_SUDDENDEATH = 31
CONST_ANI_FLASHARROW = 32
CONST_ANI_FLAMMINGARROW = 33
CONST_ANI_SHIVERARROW = 34
CONST_ANI_ENERGYBALL = 35
CONST_ANI_SMALLICE = 36
CONST_ANI_SMALLHOLY = 37
CONST_ANI_SMALLEARTH = 38
CONST_ANI_EARTHARROW = 39
CONST_ANI_EXPLOSION = 40
CONST_ANI_CAKE = 41
CONST_ANI_WEAPONTYPE = 254
CONST_ANI_NONE = 255
CONST_ANI_LAST = CONST_ANI_CAKE

TALKTYPE_FIRST = 1
TALKTYPE_SAY = TALKTYPE_FIRST
TALKTYPE_WHISPER = 2
TALKTYPE_YELL = 3
TALKTYPE_PRIVATE_FROM = 4
TALKTYPE_PRIVATE_TO = 5
TALKTYPE_CHANNEL = 7
TALKTYPE_CHANNEL_HIGHLIGHT = 8
TALKTYPE_SPELL = 9
TALKTYPE_PRIVATE_NP = 10
TALKTYPE_PRIVATE_PN = 11
TALKTYPE_GAMEMASTER_BROADCAST = 12
TALKTYPE_GAMEMASTER_CHANNEL = 13
TALKTYPE_GAMEMASTER_PRIVATE_FROM = 14
TALKTYPE_GAMEMASTER_PRIVATE_TO = 15
TALKTYPE_MONSTER_SAY = 34
TALKTYPE_MONSTER_YELL = 35

TALKTYPE_FIRST = TALKTYPE_SAY
TALKTYPE_LAST = TALKTYPE_GAMEMASTER_PRIVATE_TO
TALKTYPE_MONSTER_FIRST = TALKTYPE_MONSTER_SAY
TALKTYPE_MONSTER_LAST = TALKTYPE_MONSTER_YELL

TALKTYPE_TYPES = {
	["say"] = TALKTYPE_SAY,
	["whisper"] = TALKTYPE_WHISPER,
	["yell"] = TALKTYPE_YELL,
	["private-playernpc"] = TALKTYPE_PRIVATE_PN,
	["private-npcplayer"] = TALKTYPE_PRIVATE_NP,
	["private"] = TALKTYPE_PRIVATE_FROM,
	["channel-yellow"] = TALKTYPE_CHANNEL,
	["channel-white"] = TALKTYPE_CHANNEL_MANAGEMENT,
	["broadcast"] = TALKTYPE_GAMEMASTER_BROADCAST,
	["channel-red"] = TALKTYPE_GAMEMASTER_CHANNEL,
	["private-red"] = TALKTYPE_GAMEMASTER_PRIVATE_FROM,
	["channel-orange"] = TALKTYPE_CHANNEL_HIGHLIGHT,
	["monster"] = TALKTYPE_MONSTER_SAY,
	["monster-yell"] = TALKTYPE_MONSTER_YELL
}

MESSAGE_STATUS_CONSOLE_BLUE = 4
MESSAGE_STATUS_CONSOLE_RED = 12
MESSAGE_STATUS_DEFAULT = 16
MESSAGE_STATUS_WARNING = 17
MESSAGE_EVENT_ADVANCE = 18
MESSAGE_STATUS_SMALL = 19
MESSAGE_INFO_DESCR = 20
MESSAGE_DAMAGE_DEALT = 21
MESSAGE_DAMAGE_RECEIVED = 22
MESSAGE_HEALED = 23
MESSAGE_EXPERIENCE = 24
MESSAGE_DAMAGE_OTHERS = 25
MESSAGE_HEALED_OTHERS = 26
MESSAGE_EXPERIENCE_OTHERS = 27
MESSAGE_EVENT_DEFAULT = 28
MESSAGE_LOOT = 29
MESSAGE_TRADE_NPC = 30
MESSAGE_EVENT_GUILD = 31
MESSAGE_PARTY_MANAGEMENT = 32
MESSAGE_PARTY = 33
MESSAGE_EVENT_ORANGE = 34
MESSAGE_STATUS_CONSOLE_ORANGE = 35
MESSAGE_REPORT = 36
MESSAGE_HOTKEY_USE = 37
MESSAGE_TUTORIAL_HINT = 38

MESSAGE_FIRST = MESSAGE_STATUS_CONSOLE_BLUE
MESSAGE_LAST = MESSAGE_TUTORIAL_HINT

MESSAGE_TYPES = {
	["advance"] = MESSAGE_EVENT_ADVANCE,
	["event"] = MESSAGE_EVENT_DEFAULT,
	["white"] = MESSAGE_EVENT_DEFAULT,
	["orange"] = MESSAGE_STATUS_CONSOLE_ORANGE,
	["info"] = MESSAGE_INFO_DESCR,
	["green"] = MESSAGE_INFO_DESCR,
	["small"] = MESSAGE_STATUS_SMALL,
	["blue"] = MESSAGE_STATUS_CONSOLE_BLUE,
	["red"] = MESSAGE_STATUS_CONSOLE_RED,
	["warning"] = MESSAGE_STATUS_WARNING,
	["status"] = MESSAGE_STATUS_DEFAULT
}

COLOR_BLACK = 0
COLOR_BLUE = 5
COLOR_GREEN = 18
COLOR_LIGHTGREEN = 66
COLOR_DARKBROWN = 78
COLOR_LIGHTBLUE = 89
COLOR_MAYABLUE = 95
COLOR_DARKRED = 108
COLOR_DARKPURPLE = 112
COLOR_BROWN = 120
COLOR_GREY = 129
COLOR_TEAL = 143
COLOR_DARKPINK = 152
COLOR_PURPLE = 154
COLOR_DARKORANGE = 156
COLOR_RED = 180
COLOR_PINK = 190
COLOR_ORANGE = 192
COLOR_DARKYELLOW = 205
COLOR_YELLOW = 210
COLOR_WHITE = 215
COLOR_NONE = 255

MAPMARK_TICK = 0
MAPMARK_QUESTION = 1
MAPMARK_EXCLAMATION = 2
MAPMARK_STAR = 3
MAPMARK_CROSS = 4
MAPMARK_TEMPLE = 5
MAPMARK_KISS = 6
MAPMARK_SHOVEL = 7
MAPMARK_SWORD = 8
MAPMARK_FLAG = 9
MAPMARK_LOCK = 10
MAPMARK_BAG = 11
MAPMARK_SKULL = 12
MAPMARK_DOLLAR = 13
MAPMARK_REDNORTH = 14
MAPMARK_REDSOUTH = 15
MAPMARK_REDEAST = 16
MAPMARK_REDWEST = 17
MAPMARK_GREENNORTH = 18
MAPMARK_GREENSOUTH = 19

ITEM_TYPE_NONE = 0
ITEM_TYPE_DEPOT = 1
ITEM_TYPE_MAILBOX = 2
ITEM_TYPE_TRASHHOLDER = 3
ITEM_TYPE_CONTAINER = 4
ITEM_TYPE_DOOR = 5
ITEM_TYPE_MAGICFIELD = 6
ITEM_TYPE_TELEPORT = 7
ITEM_TYPE_BED = 8
ITEM_TYPE_KEY = 9
ITEM_TYPE_RUNE = 10

ITEM_GROUP_NONE = 0
ITEM_GROUP_GROUND = 1
ITEM_GROUP_CONTAINER = 2
ITEM_GROUP_CHARGES = 6
ITEM_GROUP_SPLASH = 11
ITEM_GROUP_FLUID = 12

CONST_PROP_BLOCKSOLID = 0
CONST_PROP_HASHEIGHT = 1
CONST_PROP_BLOCKPROJECTILE = 2
CONST_PROP_BLOCKPATHFIND = 3
CONST_PROP_ISVERTICAL = 4
CONST_PROP_ISHORIZONTAL = 5
CONST_PROP_MOVABLE = 6
CONST_PROP_BLOCKINGANDNOTMOVABLE = 7
CONST_PROP_SUPPORTHANGABLE = 8

CHASEMODE_STANDSTILL = 0
CHASEMODE_FOLLOW = 1

FIGHTMODE_ATTACK = 0
FIGHTMODE_BALANCED = 1
FIGHTMODE_DEFENSE = 2

SECUREMODE_ON = 0
SECUREMODE_OFF = 1

TRADE_NONE = 0
TRADE_INITIATED = 1
TRADE_ACCEPT = 2
TRADE_ACKNOWLEDGE = 3
TRADE_TRANSFER = 4

MANAGER_NONE = 0
MANAGER_NEW = 1
MANAGER_ACCOUNT = 2
MANAGER_NAMELOCK = 3

PLAYERSEX_FEMALE = 0
PLAYERSEX_MALE = 1

PLAYERLOSS_EXPERIENCE = 0
PLAYERLOSS_MANA = 1
PLAYERLOSS_SKILLS = 2
PLAYERLOSS_CONTAINERS = 3
PLAYERLOSS_ITEMS = 4

STATSCHANGE_HEALTHGAIN = 0
STATSCHANGE_HEALTHLOSS = 1
STATSCHANGE_MANAGAIN = 2
STATSCHANGE_MANALOSS = 3

SKILL_FIRST = 0
SKILL_FIST = SKILL_FIRST
SKILL_CLUB = 1
SKILL_SWORD = 2
SKILL_AXE = 3
SKILL_DISTANCE = 4
SKILL_SHIELD = 5
SKILL_FISHING = 6
SKILL__MAGLEVEL = 7
SKILL__LEVEL = 8
SKILL__EXPERIENCE = 9
SKILL_LAST = SKILL_FISHING
SKILL__PRE_LAST = SKILL__LEVEL
SKILL__LAST = SKILL__EXPERIENCE

SKILL_NAMES = {
	[SKILL_FIST] = "fist fighting",
	[SKILL_CLUB] = "club fighting",
	[SKILL_SWORD] = "sword fighting",
	[SKILL_AXE] = "axe fighting",
	[SKILL_DISTANCE] = "distance fighting",
	[SKILL_SHIELD] = "shielding",
	[SKILL_FISHING] = "fishing",
	[SKILL__LEVEL] = "level",
	[SKILL__MAGLEVEL] = "magic level"
}

SKILL_IDS = {
	["fist"] = SKILL_FIST,
	["club"] = SKILL_CLUB,
	["sword"] = SKILL_SWORD,
	["axe"] = SKILL_AXE,
	["distance"] = SKILL_DISTANCE,
	["dist"] = SKILL_DISTANCE,
	["shielding"] = SKILL_SHIELD,
	["shield"] = SKILL_SHIELD,
	["fishing"] = SKILL_FISHING,
	["fish"] = SKILL_FISHING,
	["level"] = SKILL__LEVEL,
	["magic"] = SKILL__MAGLEVEL
}

GUILD_MEMBER = 1
GUILD_VICE = 2
GUILD_LEADER = 3

SKULL_NONE = 0
SKULL_YELLOW = 1
SKULL_GREEN = 2
SKULL_WHITE = 3
SKULL_RED = 4
SKULL_BLACK = 5
SKULL_ORANGE = 6
SKULL_LAST = SKULL_ORANGE

SHIELD_NONE = 0
SHIELD_WHITEYELLOW = 1
SHIELD_WHITEBLUE = 2
SHIELD_BLUE = 3
SHIELD_YELLOW = 4
SHIELD_BLUE_SHAREDEXP = 5
SHIELD_YELLOW_SHAREDEXP = 6
SHIELD_BLUE_NOSHAREDEXP_BLINK = 7
SHIELD_YELLOW_NOSHAREDEXP_BLINK = 8
SHIELD_BLUE_NOSHAREDEXP = 9
SHIELD_YELLOW_NOSHAREDEXP = 10
SHIELD_LAST = SHIELD_YELLOW_NOSHAREDEXP

EMBLEM_NONE = 0
EMBLEM_GREEN = 1
EMBLEM_RED = 2
EMBLEM_BLUE = 3

WORLDTYPE_OPTIONAL = 1
WORLDTYPE_OPEN = 2
WORLDTYPE_HARDCORE = 3

DATABASE_NONE = 0
DATABASE_MYSQL = 1
DATABASE_SQLITE = 2
DATABASE_POSTGRESQL = 3

GAMESTATE_STARTUP = 1
GAMESTATE_INIT = 2
GAMESTATE_NORMAL = 3
GAMESTATE_MAINTAIN = 4
GAMESTATE_CLOSED = 5
GAMESTATE_CLOSING = 6
GAMESTATE_SHUTDOWN = 7

RELOAD_ACTIONS = 1
RELOAD_CHAT = 2
RELOAD_CONFIG = 3
RELOAD_CREATUREEVENTS = 4
RELOAD_GAMESERVERS = 5
RELOAD_GLOBALEVENTS = 6
RELOAD_GROUPS = 7
RELOAD_HIGHSCORES = 8
RELOAD_ITEMS = 10
RELOAD_MONSTERS = 11
RELOAD_MOUNTS = 12
RELOAD_MOVEEVENTS = 13
RELOAD_NPCS = 14
RELOAD_OUTFITS = 15
RELOAD_QUESTS = 16
RELOAD_RAIDS = 17
RELOAD_SPELLS = 18
RELOAD_STAGES = 19
RELOAD_TALKACTIONS = 20
RELOAD_VOCATIONS = 21
RELOAD_WEAPONS = 22
RELOAD_MODS = 23
RELOAD_ALL = 24

BAN_NONE = 0
BAN_IP = 1
BAN_PLAYER = 2
BAN_ACCOUNT = 3
BAN_NOTATION = 4
BAN_STATEMENT = 5

PLAYERBAN_NONE = 0
PLAYERBAN_REPORT = 1
PLAYERBAN_LOCK = 2
PLAYERBAN_BANISHMENT = 3

CHANNEL_GUILD = 0
CHANNEL_PARTY = 1
CHANNEL_HELP = 7
CHANNEL_DEFAULT = 0xFFFE
CHANNEL_PRIVATE = 0xFFFF

STACKPOS_GROUND = 0
STACKPOS_TOP_CREATURE = 253
STACKPOS_TOP_FIELD = 254
STACKPOS_TOP_MOVABLE_ITEM_OR_CREATURE = 255

WEAPON_NONE = 0
WEAPON_SWORD = 1
WEAPON_CLUB = 2
WEAPON_AXE = 3
WEAPON_DIST = 4
WEAPON_SHIELD = 5
WEAPON_FIST = 6
WEAPON_WAND = 7
WEAPON_AMMO = 8

ACTION_NOTATION = 0
ACTION_NAMEREPORT = 1
ACTION_BANISHMENT = 2
ACTION_BANREPORT = 3
ACTION_BANFINAL = 4
ACTION_BANREPORTFINAL = 5
ACTION_STATEMENT = 6
ACTION_DELETION = 7
ACTION_NAMELOCK = 8
ACTION_BANLOCK = 9
ACTION_BANLOCKFINAL = 10
ACTION_PLACEHOLDER = 11

RECURSE_FIRST = -1
RECURSE_NONE = 0
RECURSE_ALL = 1

ITEM_GOLD_COIN = 2148
ITEM_PLATINUM_COIN = 2152
ITEM_CRYSTAL_COIN = 2160
ITEM_SCARAB_COIN = 2159
ITEM_FISH = 2667
ITEM_WORM = 3976
ITEM_MECHANICAL_FISH = 10224
ITEM_NAIL = 8309
ITEM_MECHANICAL_FISHING_ROD = 10223
ITEM_GREEN_PERCH = 7159
ITEM_RAINBOW_TROUT = 7158
ITEM_NORTHERN_PIKE = 2669
ITEM_PARCEL = 2595
ITEM_LABEL = 2599
ITEM_ACTION_BOOK = 1977

RETURNVALUE_NOERROR = 0
RETURNVALUE_NOTPOSSIBLE = 1
RETURNVALUE_NOTENOUGHROOM = 2
RETURNVALUE_PLAYERISPZLOCKED = 3
RETURNVALUE_PLAYERISNOTINVITED = 4
RETURNVALUE_CANNOTTHROW = 5
RETURNVALUE_THEREISNOWAY = 6
RETURNVALUE_DESTINATIONOUTOFREACH = 7
RETURNVALUE_CREATUREBLOCK = 8
RETURNVALUE_NOTMOVABLE = 9
RETURNVALUE_DROPTWOHANDEDITEM = 10
RETURNVALUE_BOTHHANDSNEEDTOBEFREE = 11
RETURNVALUE_CANONLYUSEONEWEAPON = 12
RETURNVALUE_NEEDEXCHANGE = 13
RETURNVALUE_CANNOTBEDRESSED = 14
RETURNVALUE_PUTTHISOBJECTINYOURHAND = 15
RETURNVALUE_PUTTHISOBJECTINBOTHHANDS = 16
RETURNVALUE_TOOFARAWAY = 17
RETURNVALUE_FIRSTGODOWNSTAIRS = 18
RETURNVALUE_FIRSTGOUPSTAIRS = 19
RETURNVALUE_CONTAINERNOTENOUGHROOM = 20
RETURNVALUE_NOTENOUGHCAPACITY = 21
RETURNVALUE_CANNOTPICKUP = 22
RETURNVALUE_THISISIMPOSSIBLE = 23
RETURNVALUE_DEPOTISFULL = 24
RETURNVALUE_CREATUREDOESNOTEXIST = 25
RETURNVALUE_CANNOTUSETHISOBJECT = 26
RETURNVALUE_PLAYERWITHTHISNAMEISNOTONLINE = 27
RETURNVALUE_NOTREQUIREDLEVELTOUSERUNE = 28
RETURNVALUE_YOUAREALREADYTRADING = 29
RETURNVALUE_THISPLAYERISALREADYTRADING = 30
RETURNVALUE_YOUMAYNOTLOGOUTDURINGAFIGHT = 31
RETURNVALUE_DIRECTPLAYERSHOOT = 32
RETURNVALUE_NOTENOUGHLEVEL = 33
RETURNVALUE_NOTENOUGHMAGICLEVEL = 34
RETURNVALUE_NOTENOUGHMANA = 35
RETURNVALUE_NOTENOUGHSOUL = 36
RETURNVALUE_YOUAREEXHAUSTED = 37
RETURNVALUE_PLAYERISNOTREACHABLE = 38
RETURNVALUE_CANONLYUSETHISRUNEONCREATURES = 39
RETURNVALUE_ACTIONNOTPERMITTEDINPROTECTIONZONE = 40
RETURNVALUE_YOUMAYNOTATTACKTHISPLAYER = 41
RETURNVALUE_YOUMAYNOTATTACKAPERSONINPROTECTIONZONE = 42
RETURNVALUE_YOUMAYNOTATTACKAPERSONWHILEINPROTECTIONZONE = 43
RETURNVALUE_YOUMAYNOTATTACKTHISCREATURE = 44
RETURNVALUE_YOUCANONLYUSEITONCREATURES = 45
RETURNVALUE_CREATUREISNOTREACHABLE = 46
RETURNVALUE_TURNSECUREMODETOATTACKUNMARKEDPLAYERS = 47
RETURNVALUE_YOUNEEDPREMIUMACCOUNT = 48
RETURNVALUE_YOUNEEDTOLEARNTHISSPELL = 49
RETURNVALUE_YOURVOCATIONCANNOTUSETHISSPELL = 50
RETURNVALUE_YOUNEEDAWEAPONTOUSETHISSPELL = 51
RETURNVALUE_PLAYERISPZLOCKEDLEAVEPVPZONE = 52
RETURNVALUE_PLAYERISPZLOCKEDENTERPVPZONE = 53
RETURNVALUE_ACTIONNOTPERMITTEDINANOPVPZONE = 54
RETURNVALUE_YOUCANNOTLOGOUTHERE = 55
RETURNVALUE_YOUNEEDAMAGICITEMTOCASTSPELL = 56
RETURNVALUE_CANNOTCONJUREITEMHERE = 57
RETURNVALUE_TILEISFULL = 58
RETURNVALUE_NAMEISTOOAMBIGUOUS = 59
RETURNVALUE_CANONLYUSEONESHIELD = 60
RETURNVALUE_YOUARENOTTHEOWNER = 61
RETURNVALUE_YOUMAYNOTCASTAREAONBLACKSKULL = 62
RETURNVALUE_NOTENOUGHSKILL = 63

CONTAINER_POSITION = 0xFFFF
EMPTY_STORAGE = -1
EMPTY_RESULT = -1
ITEMCOUNT_MAX = 100

WAR_GUILD = 0
WAR_ENEMY = 1

AUTOID_PLAYERS = 0x10000000
AUTOID_MONSTERS = 0x40000000
AUTOID_NPCS = 0x80000000

PLAYERFLAG_CANNOTUSECOMBAT = 0
PLAYERFLAG_CANNOTATTACKPLAYER = 1
PLAYERFLAG_CANNOTATTACKMONSTER = 2
PLAYERFLAG_CANNOTBEATTACKED = 3
PLAYERFLAG_CANCONVINCEALL = 4
PLAYERFLAG_CANSUMMONALL = 5
PLAYERFLAG_CANILLUSIONALL = 6
PLAYERFLAG_CANSENSEINVISIBILITY = 7
PLAYERFLAG_IGNOREDBYMONSTERS = 8
PLAYERFLAG_NOTGAININFIGHT = 9
PLAYERFLAG_HASINFINITEMANA = 10
PLAYERFLAG_HASINFINITESOUL = 11
PLAYERFLAG_HASNOEXHAUSTION = 12
PLAYERFLAG_CANNOTUSESPELLS = 13
PLAYERFLAG_CANNOTPICKUPITEM = 14
PLAYERFLAG_CANALWAYSLOGIN = 15
PLAYERFLAG_CANBROADCAST = 16
PLAYERFLAG_CANEDITHOUSES = 17
PLAYERFLAG_CANNOTBEBANNED = 18
PLAYERFLAG_CANNOTBEPUSHED = 19
PLAYERFLAG_HASINFINITECAPACITY = 20
PLAYERFLAG_CANPUSHALLCREATURES = 21
PLAYERFLAG_CANTALKREDPRIVATE = 22
PLAYERFLAG_CANTALKREDCHANNEL = 23
PLAYERFLAG_TALKORANGEHELPCHANNEL = 24
PLAYERFLAG_NOTGAINEXPERIENCE = 25
PLAYERFLAG_NOTGAINMANA = 26
PLAYERFLAG_NOTGAINHEALTH = 27
PLAYERFLAG_NOTGAINSKILL = 28
PLAYERFLAG_SETMAXSPEED = 29
PLAYERFLAG_SPECIALVIP = 30
PLAYERFLAG_NOTGENERATELOOT = 31
PLAYERFLAG_CANTALKREDCHANNELANONYMOUS = 32
PLAYERFLAG_IGNOREPROTECTIONZONE = 33
PLAYERFLAG_IGNORESPELLCHECK = 34
PLAYERFLAG_IGNOREWEAPONCHECK = 35
PLAYERFLAG_CANNOTBEMUTED = 36
PLAYERFLAG_ISALWAYSPREMIUM = 37
PLAYERFLAG_38 = 38 -- ignore
PLAYERFLAG_39 = 39 -- ignore
PLAYERFLAG_SHOWGROUPINSTEADOFVOCATION = 40
PLAYERFLAG_HASINFINITESTAMINA = 41
PLAYERFLAG_CANNOTMOVEITEMS = 42
PLAYERFLAG_CANNOTMOVECREATURES = 43
PLAYERFLAG_CANREPORTBUGS = 44
PLAYERFLAG_45 = 45 -- ignore
PLAYERFLAG_CANNOTBESEEN = 46
PLAYERFLAG_HIDEHEALTH = 47
PLAYERFLAG_CANPASSTHROUGHALLCREATURES = 48

PLAYERCUSTOMFLAG_ALLOWIDLE = 0
PLAYERCUSTOMFLAG_CANSEEPOSITION	= 1
PLAYERCUSTOMFLAG_CANSEEITEMDETAILS = 2
PLAYERCUSTOMFLAG_CANSEECREATUREDETAILS = 3
PLAYERCUSTOMFLAG_NOTSEARCHABLE = 4
PLAYERCUSTOMFLAG_GAMEMASTERPRIVILEGES = 5
PLAYERCUSTOMFLAG_CANTHROWANYWHERE = 6
PLAYERCUSTOMFLAG_CANPUSHALLITEMS = 7
PLAYERCUSTOMFLAG_CANMOVEANYWHERE = 8
PLAYERCUSTOMFLAG_CANMOVEFROMFAR = 9
PLAYERCUSTOMFLAG_CANUSEFAR = 10
PLAYERCUSTOMFLAG_CANLOGINMULTIPLECHARACTERS = 11
PLAYERCUSTOMFLAG_CANLOGOUTANYTIME = 12
PLAYERCUSTOMFLAG_HIDELEVEL = 13
PLAYERCUSTOMFLAG_ISPROTECTED = 14
PLAYERCUSTOMFLAG_ISIMMUNE = 15
PLAYERCUSTOMFLAG_NOTGAINSKULL = 16
PLAYERCUSTOMFLAG_NOTGAINUNJUSTIFIED = 17
PLAYERCUSTOMFLAG_IGNOREPACIFICATION = 18
PLAYERCUSTOMFLAG_IGNORELOGINDELAY = 19
PLAYERCUSTOMFLAG_CANSTAIRHOP = 20
PLAYERCUSTOMFLAG_CANTURNHOP = 21
PLAYERCUSTOMFLAG_IGNOREHOUSERENT = 22
PLAYERCUSTOMFLAG_CANWEARALLADDONS = 23
PLAYERCUSTOMFLAG_ISWALKABLE = 24
PLAYERCUSTOMFLAG_CANUSEALLMOUNTS = 25
PLAYERCUSTOMFLAG_HASFULLLIGHT = 26

maleOutfits = {128, 129, 130, 131, 132, 133, 134, 143, 144, 145, 146, 151, 152, 153, 154, 251, 268, 273, 278, 289, 325, 328, 335, 367, 430, 432, 463, 465, 472}
femaleOutfits = {136, 137, 138, 139, 140, 141, 142, 147, 148, 149, 150, 155, 156, 157, 158, 252, 269, 270, 279, 288, 324, 329, 336, 366, 431, 433, 464, 466, 471}
mountOutfits = {368, 369, 370, 371, 372, 373, 374, 375, 376, 377, 378, 379, 387, 388, 389, 390, 392, 401, 402, 405, 406, 421, 426, 437, 438, 447, 450}

underWater = {5405, 5406, 5407, 5408, 5409, 5410}

enchantableGems = {2147, 2146, 2149, 2150}
enchantableItems = {2383, 7383, 7384, 7406, 7402, 2429, 2430, 7389, 7380, 2454, 2423, 2445, 7415, 7392, 2391, 2544, 8905}

enchantingAltars = {
	{7504, 7505, 7506, 7507},
	{7508, 7509, 7510, 7511},
	{7516, 7517, 7518, 7519},
	{7512, 7513, 7514, 7515}
}

enchantedGems = {7760, 7759, 7761, 7762}
enchantedItems = {
	[2383] = {7744, 7763, 7854, 7869},
	[7383] = {7745, 7764, 7855, 7870},
	[7384] = {7746, 7765, 7856, 7871},
	[7406] = {7747, 7766, 7857, 7872},
	[7402] = {7748, 7767, 7858, 7873},
	[2429] = {7749, 7768, 7859, 7874},
	[2430] = {7750, 7769, 7860, 7875},
	[7389] = {7751, 7770, 7861, 7876},
	[7380] = {7752, 7771, 7862, 7877},
	[2454] = {7753, 7772, 7863, 7878},
	[2423] = {7754, 7773, 7864, 7879},
	[2445] = {7755, 7774, 7865, 7880},
	[7415] = {7756, 7775, 7866, 7881},
	[7392] = {7757, 7776, 7867, 7882},
	[2391] = {7758, 7777, 7868, 7883},
	[2544] = {7840, 7839, 7850, 7838},
	[8905] = {8906, 8907, 8909, 8908}
}

Config_meta =
{
	__index = function(t, k)
		if(k == "type") then
			return function()
				return "Config"
			end
		end

		return getConfigValue(k)
	end,

	__newindex = function(t, k, v)
		return false
	end
}

CONFIG = {}
setmetatable(CONFIG, Config_meta)

Storage_meta =
{
	__index = function(t, k)
		if(k == "type") then
			return function()
				return "Storage"
			end
		end

		return getStorage(k)
	end,

	__newindex = function(t, k, v)
		return doSetStorage(k, v)
	end
}

STORAGE = {}
setmetatable(STORAGE, Storage_meta)
