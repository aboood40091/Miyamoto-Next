#include <Preferences.h>
#include <actor/ActorCreateMgr.h>
#include <enemy/Kuribo.h>
#include <enemy/Nokonoko.h>
#include <map_obj/ActorBlockBigHatena.h>
#include <map_obj/ActorBlockBigRenga.h>
#include <map_obj/ActorBlockHatena.h>
#include <map_obj/ActorBlockRenga.h>
#include <map_obj/ActorCoin.h>
#include <map_obj/CollectionCoin.h>
#include <map_obj/DokanJoint.h>
#include <map_obj/GoalPole.h>
#include <map_obj/ObjDokanActorDown.h>
#include <map_obj/ObjDokanActorDownNextGoto.h>
#include <map_obj/ObjDokanActorLeft.h>
#include <map_obj/ObjDokanActorLeftNextGoto.h>
#include <map_obj/ObjDokanActorRight.h>
#include <map_obj/ObjDokanActorRightNextGoto.h>
#include <map_obj/ObjDokanActorUp.h>
#include <map_obj/ObjDokanActorUpNextGoto.h>

ActorCreateMgr* ActorCreateMgr::sInstance = nullptr;

bool ActorCreateMgr::createSingleton()
{
    if (sInstance)
        return false;

    sInstance = new ActorCreateMgr();
    return true;
}

void ActorCreateMgr::destroySingleton()
{
    if (!sInstance)
        return;

    delete sInstance;
    sInstance = nullptr;
}

ActorCreateMgr::ActorCreateMgr()
{
    initialize();
}

void ActorCreateMgr::initialize()
{
    mMapActorNameMap.clear();
    mActorFactoryMap.clear();
    mTypeMaxNum = 0;

    mNameLanguage = Preferences::instance()->getActorNameLanguage();

    // -------------------------------------------------------------

    setTypeMaxNum(724);

    // -------------------------------------------------------------

    setName(  0, u8"クリボー", "Goomba");
    setName(  1, u8"パタクリボー", "Paragoomba");
    setName(  2, u8"上向き土管パックンフラワー", "Pipe Piranha Plant - Up");
    setName(  3, u8"下向き土管パックンフラワー", "Pipe Piranha Plant - Down");
    setName(  4, u8"左向き土管パックンフラワー", "Pipe Piranha Plant - Left");
    setName(  5, u8"右向き土管パックンフラワー", "Pipe Piranha Plant - Right");
    setName(  6, u8"上向き土管ファイヤパックンフラワー", "Pipe Fire Piranha Plant - Up");
    setName(  7, u8"下向き土管ファイヤパックンフラワー", "Pipe Fire Piranha Plant - Down");
    setName(  8, u8"左向き土管ファイヤパックンフラワー", "Pipe Fire Piranha Plant - Left [UNUSED]");
    setName(  9, u8"右向き土管ファイヤパックンフラワー", "Pipe Fire Piranha Plant - Right [UNUSED]");
    setName( 10, u8"上向き土管アイスパックンフラワー", "Pipe Ice Piranha Plant - Up");
    setName( 11, u8"下向き土管アイスパックンフラワー", "Pipe Ice Piranha Plant - Down");
    setName( 12, u8"左向き土管アイスパックンフラワー", "Pipe Ice Piranha Plant - Left [UNUSED]");
    setName( 13, u8"右向き土管アイスパックンフラワー", "Pipe Ice Piranha Plant - Right [UNUSED]");
    setName( 14, u8"地面パックンフラワー", "Grounded Piranha Plant");
    setName( 15, u8"地面ファイヤーパックンフラワー", "Grounded Fire Piranha Plant");
    setName( 16, u8"地面アイスパックンフラワー", "Grounded Ice Piranha Plant");
    setName( 17, u8"地面大パックンフラワー", "Giant Grounded Piranha Plant");
    setName( 18, u8"地面ファイヤ大パックンフラワー", "Giant Grounded Fire Piranha Plant");
    setName( 19, u8"ノコノコ", "Koopa Troopa");
    setName( 20, u8"パタパタ", "Koopa Paratroopa");
    setName( 21, u8"グループパタパタ", "Grouped Koopa Paratroopa");
    setName( 22, u8"メット", "Buzzy Beetle");
    setName( 23, u8"トゲゾー", "Spiny");
    setName( 24, u8"逆さトゲゾー", "Upside-down Spiny [UNUSED]");
    setName( 25, u8"中間ポイントの旗", "Checkpoint Flag");
    setName( 26, u8"ズーム君", "Zoom Area");
    setName( 27, u8"マックス上君（左）", "Vertical Scroll Limit - Left");
    setName( 28, u8"マックス上君（右）", "Vertical Scroll Limit - Right");
    setName( 29, u8"右ストップ君（上）", "Horizontal Scroll Limit - Top");
    setName( 30, u8"右ストップ君（下）", "Horizontal Scroll Limit - Bottom");
    setName( 31, u8"ゴールポール", "Goal Pole");
    setName( 32, u8"看板矢印", "Arrow Signboard");
    setName( 33, u8"ゴロゴロ", "Grrrol (Spawned by 188) [UNUSED]");
    setName( 34, u8"ゴロゴロ（巨大）", "Big Grrrol (duplicate) [UNUSED]");
    setName( 35, u8"ワカメ", "Seaweed");
    setName( 36, u8"フラグスイッチタグ", "Event Controller - ZONE (Zone-Enter-Triggered)");
    setName( 37, u8"フラグスイッチ４スイッチ監視ＡＮＤ", "Event Controller - AND (\"if X AND Y, do Z\")");
    setName( 38, u8"フラグスイッチ４スイッチ監視ＯＲ", "Event Controller - OR (\"if X OR Y, do Z\")");
    setName( 39, u8"フラグスイッチランダム", "Event Controller - RANDOM (\"if X, do Y OR Z\") [UNUSED]");
    setName( 40, u8"フラグスイッチ変化スイッチ", "Event Controller - IF (\"if X, do Y\")");
    setName( 41, u8"フラグスイッチ条件フラグ", "Event Controller - LOCATION (Location-State-Triggered)");
    setName( 42, u8"フラグスイッチ連続ＯＮフラグ", "Event Controller - CHAINER (\"if X, do Y through Z\")");
    setName( 43, u8"フラグスイッチ一定周期ＯＮ、ＯＦＦフラグ", "Event Controller - TIMER (Timed State Switch)");
    setName( 44, u8"赤リング", "Red Coin Ring");
    setName( 45, u8"コレクションコイン", "Star Coin");
    setName( 46, u8"コレクションコイン線対応", "Star Coin - Uses Lines");
    setName( 47, u8"コレクションコインボルト対応", "Bolt-controlled Star Coin");
    setName( 48, u8"コレクション親制御", "Movement-controlled Star Coin");
    setName( 49, u8"赤コイン", "Red Coin");
    setName( 50, u8"緑コイン", "Set of Green Coins");
    setName( 51, u8"チョロプー", "Monty Mole");
    setName( 52, u8"トゲ鉄球通り穴", "Grrrol Passage");
    setName( 53, u8"フグマンネン", "Porcupuffer [UNUSED]");
    setName( 54, u8"木の実", "Yoshi Fruit");
    setName( 55, u8"ノコノコ横方向生成", "Koopa Troopa (2)");
    setName( 56, u8"フグマンネン(湧き出し)", "Porcupuffer Spawn Area");
    setName( 57, u8"フィッシュボーン", "Fish Bone");
    setName( 58, u8"ゴロゴロ", "Grrrol (duplicate) [UNUSED]");
    setName( 59, u8"アクターハテナブロック", "Question Block");
    setName( 60, u8"アクターレンガブロック", "Brick Block");
    setName( 61, u8"アクター透明ブロック", "Invisible Item Block");
    setName( 62, u8"中心君対応土管パックンフラワー（上）", "Pivotal-rotation-controlled Pipe Piranha Plant - Up");
    setName( 63, u8"歩くパックン", "Stalking Piranha Plant");
    setName( 64, u8"水面パックン", "River Piranha Plant");
    setName( 65, u8"アクターコイン", "Coin");
    setName( 66, u8"アクターポリゴン追従コイン", "Platform-following Coin");
    setName( 67, u8"バサバサ", "Swooper (Path-controlled) (+)");
    setName( 68, u8"中心君・振り子", "Movement Controller - Pivotal Rotation (Swaying)");
    setName( 69, u8"中心君・回転", "Movement Controller - Pivotal Rotation (Spinning)");
    setName( 70, u8"親子オブジェ・親", "Movement Controller - Two-Way");
    setName( 71, u8"親子オブジェ・子", "Movement-controlled Iron Tower Platform [UNUSED]");
    setName( 72, u8"親子オブジェ・子・野原用", "Movement-controlled Acorn Plains Land Block");
    setName( 73, u8"アクターコイン湧き出し", "Coin Spawner");
    setName( 74, u8"カニボー", "Huckit Crab");
    setName( 75, u8"アイスブロス", "Ice Bro.");
    setName( 76, u8"ハンマーブロス", "Hammer Bro.");
    setName( 77, u8"メガブロス", "Sledge Bro.");
    setName( 78, u8"ブーメランブロス", "Boomerang Bro.");
    setName( 79, u8"ファイアブロス", "Fire Bro.");
    setName( 80, u8"全当たりポリゴン", "Moving Tiltable Solid Iron Platform [UNUSED]");
    setName( 81, u8"全当たりポリゴン・野原用", "Moving Tiltable Solid Grass Platform [UNUSED]");
    setName( 82, u8"中心君対応土管パックンフラワー（下）", "Pivotal-rotation-controlled Pipe Piranha Plant - Down");
    setName( 83, u8"中心君対応土管パックンフラワー（左）", "Pivotal-rotation-controlled Pipe Piranha Plant - Left");
    setName( 84, u8"中心君対応土管パックンフラワー（右）", "Pivotal-rotation-controlled Pipe Piranha Plant - Right");
    setName( 85, u8"ケロンパ", "Flame Chomp");
    setName( 86, u8"ウニラ", "Urchin");
    setName( 87, u8"アクター回転制御コイン", "Pivotal-rotation-controlled Coin");
    setName( 88, u8"水地形アクター", "Water");
    setName( 89, u8"溶岩地形アクター", "Lava");
    setName( 90, u8"毒沼地形アクター", "Poison Water");
    setName( 91, u8"砂漠地形アクター", "Quicksand");
    setName( 92, u8"雲地形アクター", "Fog");
    setName( 93, u8"靄地形アクター", "Ghost Fog [UNUSED]");
    setName( 94, u8"トランポリン雲", "Bouncy Cloud");
    setName( 95, u8"トランポリン雲(乗ると動く)", "Move-when-on Bouncy Cloud [UNUSED]");
    setName( 96, u8"松明の炎", "Lighting - Pivotal-rotation-controlled Lamp/Candle");
    setName( 97, u8"ＢＧ中心くん", "Background Center-er");
    setName( 98, u8"土管湧き出し敵", "Enemy Generator for Pipe");
    setName( 99, u8"でかウニラ", "Mega Urchin");
    setName(100, u8"レール動作の全あたりポリゴン・親", "Movement Controller - Path");
    setName(101, u8"プクプク", "Cheep Cheep");
    setName(102, u8"環境現象くん", "Nothing. (\"Environmental phenomena kun\") [UNUSED]");
    setName(103, u8"回転キラー砲台", "Bill Blaster Turret (Bullet Bill Cannon, Bullet Bill Launcher)");
    setName(104, u8"スイッチはてなボタン", "Event Controller - \"?\" Switch");
    setName(105, u8"スイッチＰボタン", "Event Controller - \"P\" Switch (Blue)");
    setName(106, u8"プクプク(湧き出し)", "Cheep Cheep Spawn Location [UNUSED]");
    setName(107, u8"普通のドア", "Peach's Castle Door");
    setName(108, u8"お化け屋敷のドア", "Ghost House Door");
    setName(109, u8"砦のドア", "Tower Boss Door");
    setName(110, u8"城のドア", "Castle Boss Door");
    setName(111, u8"クッパドア", "Bowser Boss Door");
    setName(112, u8"多砲身キラー砲台", "Bill Blaster Turret (Bullet Bill Cannon, Bullet Bill Launcher) [UNUSED]");
    setName(113, u8"プクプク（中）", "Medium-sized Cheep Cheep");
    setName(114, u8"プクプク(フォーメーション)", "Cheep Cheep Formation [UNUSED]");
    setName(115, u8"ＮＥＸＴＧＯＴＯブロック", "Special Exit Controller");
    setName(116, u8"中心君・振り子・レール対応版", "Movement Controller - Pivotal Rotation (Swaying, Path-controlled)");
    setName(117, u8"中心君対応グルグル", "Pivotal-rotation-controlled Pendulum (Spinner, Ball 'n' Chain)");
    setName(118, u8"中心君・回転・レール対応版", "Movement Controller - Pivotal Rotation (Spinning, Path-controlled)");
    setName(119, u8"ジュゲム雲", "Lakitu Cloud");
    setName(120, u8"トゲプク", "Spiny Cheep Cheep");
    setName(121, u8"霧範囲指定君", "Cloud Area");
    setName(122, u8"霧範囲指定君(ライト版)", "Light Cloud Area");
    setName(123, u8"間欠泉(砂)", "Sand Spout");
    setName(124, u8"常駐間欠泉(砂)", "Location-triggered Sand Spout");
    setName(125, u8"キラー", "Bullet Bill [UNUSED]");
    setName(126, u8"マグナムキラー", "Banzai Bill [UNUSED]");
    setName(127, u8"サーチキラー", "Bull's-Eye Bill [UNUSED]");
    setName(128, u8"マグナムサーチキラー", "Bull's-Eye Banzai Bill [UNUSED]");
    setName(129, u8"飛びプク", "Jumping Cheep Cheep");
    setName(130, u8"湧き出しジュゲム", "Lakitu Spawn Area");
    setName(131, u8"飛びプク(湧き出し)", "Jumping Cheep Cheep Spawn Area");
    setName(132, u8"回転板", "Shifting Rectangle Platforms");
    setName(133, u8"慣性線リフト", "Spine Coaster");
    setName(134, u8"泡発生管理君", "Nothing. (\"Foam generation management kun\") [UNUSED]");
    setName(135, u8"ドッスン", "Thwomp");
    setName(136, u8"ドッスン（大）", "Big Thwomp");
    setName(137, u8"カロン", "Dry Bones");
    setName(138, u8"カロン(大)", "Big Dry Bones");
    setName(139, u8"OBJ土管(上)", "Pipe - Up");
    setName(140, u8"OBJ土管(下)", "Pipe - Down");
    setName(141, u8"OBJ土管(左)", "Pipe - Left");
    setName(142, u8"OBJ土管(右)", "Pipe - Right");
    setName(143, u8"チビヨッシー(雲)", "'Cloud' Baby Yoshi [UNUSED]");
    setName(144, u8"バルーン", "Powerup / Player Bubble [UNUSED]");
    setName(145, u8"椰子の木", "Palm Tree");
    setName(146, u8"回転土管", "Pivotal-rotation-controlled Pipe");
    setName(147, u8"アクター線対応ハテナブロック", "Question Block - Uses Lines");
    setName(148, u8"アクター線対応レンガブロック", "Brick Block - Uses Lines");
    setName(149, u8"アクター回転板追従コイン", "Shifting Rectangle Platform-controlled Coin");
    setName(150, u8"モアイ", "Stone-Eye");
    setName(151, u8"モアイ（下向き）", "Upside-down Stone-Eye");
    setName(152, u8"POWブロック", "POW Block");
    setName(153, u8"懐中電灯", "Lighting - Movement-controlled Spotlight");
    setName(154, u8"アクターパタブロック", "Flying Question Block");
    setName(155, u8"土管大砲", "Pipe Cannon");
    setName(156, u8"間欠泉(水)", "Water Geyser");
    setName(157, u8"回転砦横ブロック留め具", "Movement-controlled Bar Center");
    setName(158, u8"アクター通過コイン", "Dash Coin (Coin Outline, Pivotal-rotation-controlled)");
    setName(159, u8"伸縮土管(右)", "Expanding/Contracting Pipe - Right");
    setName(160, u8"伸縮土管(左)", "Expanding/Contracting Pipe - Left");
    setName(161, u8"伸縮土管(上)", "Expanding/Contracting Pipe - Up");
    setName(162, u8"伸縮土管(下)", "Expanding/Contracting Pipe - Down");
    setName(163, u8"常駐間欠泉(水)", "Location-triggered Water Geyser");
    setName(164, u8"ボム兵", "Bob-omb");
    setName(165, u8"親中心君コイン", "Pivotal-rotation-controlled Coin Circle");
    setName(166, u8"親中心君通過コイン", "Pivotal-rotation-controlled Dash Coin Circle");
    setName(167, u8"青コイン", "Blue Coin");
    setName(168, u8"ＯＢＪコイン監視拍手君", "Clapping Controller");
    setName(169, u8"ＯＢＪコイン常駐監視拍手君", "Clapping Controller 2");
    setName(170, u8"パラボム兵", "Parabomb");
    setName(171, u8"キラー砲台", "Bill Blaster (Bullet Bill Cannon, Bullet Bill Launcher) (+)");
    setName(172, u8"伸縮キラー砲台", "Rising/Lowering Bill Blaster (+) [UNUSED]");
    setName(173, u8"マグナムキラー砲台", "Banzai Bill Blaster / Spawner (+)");
    setName(174, u8"マグナムキラー砲台（下向き）", "Upside-down Banzai Bill Blaster (+) [UNUSED]");
    setName(175, u8"メカクッパ", "Mechakoopa (+)");
    setName(176, u8"ナナメ砲台", "Cannon");
    setName(177, u8"回転砲台", "4-Way Cannon [CRASHES] [UNUSED - NSMBW]");
    setName(178, u8"回転砲台大", "Giant 4-Way Cannon [CRASHES] [UNUSED - NSMBW]");
    setName(179, u8"敵砲台弾", "Cannonball [UNUSED]");
    setName(180, u8"ガボン", "Spike");
    setName(181, u8"ガボン（常駐）", "Spike (Stationary)");
    setName(182, u8"半当たり上下移動リフト", "Vertically-moving Platform");
    setName(183, u8"ツララ", "Falling Icicle");
    setName(184, u8"ツララ（大）", "Giant Falling Icicle");
    setName(185, u8"ツララ（固定）", "Stationary Icicle");
    setName(186, u8"半当たり左右移動リフト", "Horizontally-moving Platform");
    setName(187, u8"連結ネズミ", "Scaredy Rat");
    setName(188, u8"トゲ鉄球湧き土管", "Grrrol Spawner");
    setName(189, u8"アクターブロック雲", "Lakitu Block [CRASHES] [UNUSED - NSMBW]");
    setName(190, u8"アクター回転制御ハテナブロック", "Pivotal-rotation-controlled Question Block");
    setName(191, u8"アクター回転制御レンガブロック", "Pivotal-rotation-controlled Brick Block");
    setName(192, u8"湧き出しリフト", "Moving Platform Spawner");
    setName(193, u8"線リフト", "Platform - Uses Lines");
    setName(194, u8"ファイアスネーク", "Fire Snake");
    setName(195, u8"ルーレットブロック", "Roulette Block");
    setName(196, u8"グループＩＤ", "Group Controller");
    setName(197, u8"風発生タグ", "Unfinished wind generator [UNUSED]");
    setName(198, u8"雪発生タグ", "Snow Effect [UNUSED - NSMBW]");
    setName(199, u8"光るブロック", "Glow Block [CRASHES] [UNUSED - NSMBW]");
    setName(200, u8"オブジェキノコ", "Mushroom Platform");
    setName(201, u8"火の粉発生君", "Rising Lava Particle Generator [UNUSED]");
    setName(202, u8"プロペラブロック", "Propeller Block [CRASHES] [UNUSED - NSMBW]");
    setName(203, u8"氷ブロック(持てる)", "Portable Ice Block [UNUSED - NSMBW]");
    setName(204, u8"チョロボン", "Fuzzy");
    setName(205, u8"アクター水面ハテナブロック", "Floating Question Block [UNUSED]");
    setName(206, u8"ブンブン（Ｗ１砦）", "Boom Boom (W1 - Flailing)");
    setName(207, u8"間欠泉(溶岩)", "Lava Geyser");
    setName(208, u8"アクターブロックスイッチ", "Event Controller - Brick Block \"?\" Switch (Orange) [UNUSED]");
    setName(209, u8"アクターブロックＰスイッチ", "Event Controller - Brick Block \"P\" Switch (Blue)");
    setName(210, u8"キノコリフト", "Moving Mushroom Lift [UNUSED]");
    setName(211, u8"回転半当たり床", "Pivotal-rotation-controlled/Path-controlled Semi-solid Test Platform [UNUSED]");
    setName(212, u8"オートスクロール", "Autoscrolling Controller");
    setName(213, u8"ぶらさがりツタ", "Swinging Vine");
    setName(214, u8"回転制御君", "Movement Controller - Rotation (Spinning)");
    setName(215, u8"ジャンプ台", "Portable Springboard");
    setName(216, u8"ブンブンデモ管理タグ", "Tower Boss Controller");
    setName(217, u8"親子オブジェ・子・砦用", "Movement-controlled Tower Block [UNUSED - NSMBW]");
    setName(218, u8"テレサ", "Boo");
    setName(219, u8"ビッグテレサ", "Big Boo");
    setName(220, u8"回転拡縮テレサ（子）", "Boo Circle Boo [UNUSED]");
    setName(221, u8"回転拡縮テレサ（親）", "Boo Circle");
    setName(222, u8"スネークブロック", "Snake Block");
    setName(223, u8"ブンブン（Ｗ２砦）", "Boom Boom (W2 - flailing, spinning and jumping)");
    setName(224, u8"チビヨッシー(風船)", "Balloon Baby Yoshi [UNUSED]");
    setName(225, u8"ブンブン（Ｗ６砦）", "Boom Boom (W6 Tower)");
    setName(226, u8"氷リフト(湧き出し)", "Moving Ice Floe Spawner [UNUSED]");
    setName(227, u8"氷リフト(湧き出し・浮く)", "Moving Ice Floe [UNUSED]");
    setName(228, u8"逆振り子リフト", "Pivotal-rotation-controlled Scaffold Platform");
    setName(229, u8"キリフキー", "Foo");
    setName(230, u8"ラリー", "Larry Koopa");
    setName(231, u8"氷リフト(レール動作)", "Path-controlled Ice Floe");
    setName(232, u8"光るブロックリフト", "Lighting - Movement-controlled Glow Block");
    setName(233, u8"アクターグループ線対応ハテナブロック", "Grouped Question Block - Uses Lines [UNUSED]");
    setName(234, u8"アクターグループ線対応レンガブロック", "Grouped Brick Block - Uses Lines [UNUSED]");
    setName(235, u8"ファイアーバー", "Fire Bar");
    setName(236, u8"ファイアーバー2", "Big Fire Bar");
    setName(237, u8"書き換えブロック", "Tile God");
    setName(238, u8"ねじ回しで動く全当たり OBJ・親", "Movement Controller - Bolt");
    setName(239, u8"ねじ回しで動く全当たり OBJ・子", "Bolt-controlled Metal Platform");
    setName(240, u8"丸太", "Big Floating Log");
    setName(241, u8"スピン回転キノコ台", "Bolt Mushroom Platform");
    setName(242, u8"スピン回転キノコ台・子", "Bolt Mushroom Platform - No bolt");
    setName(243, u8"チビヨッシー(泡)", "Bubble Baby Yoshi [UNUSED]");
    setName(244, u8"コクッパの炎", "Koopaling Magic [UNUSED]");
    setName(245, u8"コクッパデモ管理タグ", "Castle Boss Controller");
    setName(246, u8"ブンブン（Ｗ４砦）", "Boom Boom (W4)");
    setName(247, u8"イガクリボー", "Prickly Goomba");
    setName(248, u8"回転枠・おばけ", "Ghost House Box Frame Platform");
    setName(249, u8"ハナチャン", "Wiggler");
    setName(250, u8"回転ブロック（全アタリ）", "Pivotal-rotation-controlled Gray Block [UNUSED]");
    setName(251, u8"空中水", "Floating Water Ball (Path-controlled)");
    setName(252, u8"縄梯子", "Rope Ladder");
    setName(253, u8"円ライト", "Lighting - Movement-controlled Circle");
    setName(254, u8"深海用照明", "Lighting - Underwater Lamp");
    setName(255, u8"マメクリボー", "Micro Goomba");
    setName(256, u8"回転ブロック・キノコ", "Pivotal-rotation-controlled Mushroom Block [NEEDS PATCH] [CRASHES] [UNUSED - NSMBW]");
    setName(257, u8"横伸縮キノコリフト", "Stretching Mushroom Platform");
    setName(258, u8"横伸縮キノコリフト（常駐）", "Stretching Mushroom Platform (Faster)");
    setName(259, u8"ブラックパックン", "Moving Muncher (Two-Way)");
    setName(260, u8"砲門", "Big Cannon");
    setName(261, u8"パタメット", "Para-Beetle");
    setName(262, u8"パタメット(大)", "Heavy Para-Beetle");
    setName(263, u8"土管水流", "Pipe Bubbles");
    setName(264, u8"間欠泉(水・ボス用)", "Water Geyser (for Boss)");
    setName(265, u8"床回転", "Rolling Hill");
    setName(266, u8"回転ブロック・お化け", "Ghost House Box (Pivotal-rotation-controlled / Path-controlled)");
    setName(267, u8"大甲羅", "Giant Koopa Shell Cave [CRASHES] [UNUSED - NSMBW]");
    setName(268, u8"冷凍ブロック", "1 x 1 Customizable Ice Block [UNUSED]");
    setName(269, u8"歯車", "Rotating Stone Gear");
    setName(270, u8"ビリキュー", "Amp");
    setName(271, u8"跳ね橋の腕", "Movement-controlled Metal Drawbridge Arm");
    setName(272, u8"跳ね橋の支柱", "Movement-controlled Metal Drawbridge Support");
    setName(273, u8"跳ね橋の留め具", "Movement-controlled Metal Drawbridge Clasp");
    setName(274, u8"回転ブロック・カラー（空用）", "Pivotal-rotation-controlled White Block");
    setName(275, u8"溶岩振り子リフト", "Pivotal-rotation-controlled Castle Platform");
    setName(276, u8"ライトクラゲ", "Jellybeam");
    setName(277, u8"アクター水面コイン", "Floating Coin");
    setName(278, u8"シーソーリフト", "Seesaw Mushroom Platform");
    setName(279, u8"アクター画面追従コイン", "Coin - Follows Screen");
    setName(280, u8"スピン線リフト", "Bolt Mushroom Platform - Uses Lines");
    setName(281, u8"アクター泡コイン", "Coin in Bubble");
    setName(282, u8"キングキラー", "King Bill");
    setName(283, u8"伸縮ブロック・親", "Stretch Block Controller");
    setName(284, u8"伸縮ブロック・子(横)", "Stretch Block");
    setName(285, u8"伸縮ブロック・子(縦) ", "Vertical Stretch Block");
    setName(286, u8"バブル", "Lava Bubble");
    setName(287, u8"水車リフト", "Wheel Platform");
    setName(288, u8"フルーツの木", "Bush");
    setName(289, u8"バーナー", "Stationary Burner");
    setName(290, u8"バーナー(大)", "Stationary Burner (Long Fire) [UNUSED]");
    setName(291, u8"同期バーナー管理OBJ", "Synced Burner Controller");
    setName(292, u8"同期バーナー", "Synced Burner");
    setName(293, u8"回転バーナー", "Rotating Burner");
    setName(294, u8"のぼり棒", "Purple Striped Climbable Pole");
    setName(295, u8"ジャンプブロック", "Note Block");
    setName(296, u8"レミー", "Lemmy Koopa");
    setName(297, u8"キノコリフト・親", "Movement Controller - Mushroom Platform");
    setName(298, u8"アコヤ貝", "Clampy");
    setName(299, u8"リモコン上昇リフトのクリンチ", "Rising Tilt-controlled Girder Controller");
    setName(300, u8"リモコン上昇定員リフト", "Rising 5-Enemy-Max Tilt-controlled Girder");
    setName(301, u8"大ハナチャン", "Giant Wiggler");
    setName(302, u8"ブンブン（Ｗ３砦）", "Boom Boom (W3)");
    setName(303, u8"コトン", "Thwimp");
    setName(304, u8"グラグラ岩", "Wobble Rock");
    setName(305, u8"ポルターガイスト", "Poltergeist item");
    setName(306, u8"氷ブロック", "kori burokku [CRASHING SPRITE] [UNUSED]");
    setName(307, u8"移動金網", "Moving Fence");
    setName(308, u8"天秤リフト", "Scale Platform [UNUSED]");
    setName(309, u8"天秤リフト戻り", "Scale Platform");
    setName(310, u8"燭台", "Candlestick [CRASHES] [UNUSED - NSMBW]");
    setName(311, u8"全当たりポリゴン・砦用", "Solid Tower Block [UNUSED - NSMBW]");
    setName(312, u8"線キノコブロック", "Line-controlled Mushroom Block [NEEDS PATCH] [CRASHES] [UNUSED - NSMBW]");
    setName(313, u8"ゲッソー", "Blooper");
    setName(314, u8"氷塊", "Crash Sprite [UNUSED]");
    setName(315, u8"天秤リフトステップ", "Scale Platform Step [UNUSED]");
    setName(316, u8"回転ブロック・地下用", "Pivotal-rotation-controlled Crystal Block");
    setName(317, u8"ブンブン（Ｗ５砦）", "Boom Boom (W5 - big, spinning and jumping)");
    setName(318, u8"同期バブル", "Grouped Lava Bubble");
    setName(319, u8"一定数乗ると動くリフト", "Move-when-on Metal Lift [CRASHES] [UNUSED - NSMBW]");
    setName(320, u8"クラッシャー", "Broozer");
    setName(321, u8"チョーチン", "Bulber");
    setName(322, u8"ゲッソー(ばら撒き)", "Blooper Nanny with Babies");
    setName(323, u8"樽ブロック", "Barrel");
    setName(324, u8"一定数乗ると動くお化けオブジェBG", "Move-when-touched Ghost House Box");
    setName(325, u8"回転制御君用通過コイン", "Rotation-controlled Coin [Outline]");
    setName(326, u8"アクター回転制御用コイン", "Rotation-controlled Coin");
    setName(327, u8"ハンマー振り子", "Pivotal-rotation-controlled Sledge Hammer Pendulum");
    setName(328, u8"ねじ回し専用コイン", "Bolt-controlled Coin");
    setName(329, u8"下向き大棍棒", "Spike Pillar - Down");
    setName(330, u8"一定数乗ると止まる溶岩リフト", "Raft with Enemy Limit");
    setName(331, u8"上向き大棍棒", "Spike Pillar - Up");
    setName(332, u8"右向き大棍棒", "Spike Pillar - Right");
    setName(333, u8"左向き大棍棒", "Spike Pillar - Left");
    setName(334, u8"ペンタロー", "Cooligan");
    setName(335, u8"ペンタロー(湧き土管)", "Cooligan Generator for Pipe");
    setName(336, u8"イバラムシ", "Bramball");
    setName(337, u8"バクバク", "Cheep Chomp [UNUSED]");
    setName(338, u8"木箱", "Wooden Box");
    setName(339, u8"木箱(湧き出し)", "Wooden Box Spawner [UNUSED]");
    setName(340, u8"回転床同期コイン", "Rolling Hill Coin");
    setName(341, u8"ナット", "Airship Nut Platform");
    setName(342, u8"右向きロング大棍棒", "Long Spike Pillar - Right");
    setName(343, u8"左向きロング大棍棒", "Long Spike Pillar - Left");
    setName(344, u8"特殊スクロールタグ", "Airship Rocking Effect");
    setName(345, u8"リモコンシーソーリフト", "Remote-controlled Seesaw Lift [CRASHES] [UNUSED - NSMBW]");
    setName(346, u8"グループコトン", "Grouped Thwimp");
    setName(347, u8"アクター石ブロック", "Stone Block");
    setName(348, u8"お手本ブロック", "Super Guide Block");
    setName(349, u8"リモコン横移動線リフト", "Tilt-controlled Girder - Uses Lines");
    setName(350, u8"回転砦横ブロック", "Pivotal-rotation-controlled Stone Block");
    setName(351, u8"サンボ", "Pokey");
    setName(352, u8"トゲメット", "Spike Top");
    setName(353, u8"パラシュートコイン親", "Parachute Coin");
    setName(354, u8"全当たり左右移動リフト", "Horizontally-moving Rotatable Iron Platform [UNUSED]");
    setName(355, u8"床回転(穴あき土管)", "Rotating Floor with Pipe (Enterable) [NEEDS PATCH] [CRASHES] [UNUSED - NSMBW]");
    setName(356, u8"全当たり上下移動リフト", "Vertically-moving Rotatable Iron Platform [UNUSED]");
    setName(357, u8"グループチョロボン", "Grouped Fuzzy");
    setName(358, u8"ねじ回しで動く足場", "Bolt-controlled Airship Platform [CRASHES] [UNUSED - NSMBW]");
    setName(359, u8"溶岩地面", "Path-controlled Lava Block");
    setName(360, u8"ねじ回しで動くワイヤー", "Bolt-controlled Airship Platform Wire [CRASHES] [UNUSED - NSMBW]");
    setName(361, u8"パラシュートコイン(湧き出し)", "Parachute Coin Spawner");
    setName(362, u8"中心君対応土管ファイヤーパックン", "Pivotal-rotation-controlled Pipe Fire Piranha Plant");
    setName(363, u8"宝箱", "Treasure Chest");
    setName(364, u8"火山弾管理オブジェ", "Volcano Rock Spawner");
    setName(365, u8"チビヨッシー(光る)", "Glow Baby Yoshi [UNUSED]");
    setName(366, u8"コインヘビ親", "Rotating Coin Snake [UNUSED]");
    setName(367, u8"一定数乗ると動く半当たりリフト", "Move-when-on Platform");
    setName(368, u8"モートン", "Boss - Morton");
    setName(369, u8"南京玉すだれコイン・親", "Pivotal-rotation-controlled Folding Coins [UNUSED]");
    setName(370, u8"アクターキノコリフト追従コイン", "Moving Mushroom Platform Coin [UNUSED]");
    setName(371, u8"レール動作の全あたりポリゴン・子", "Path-controlled Test Platform");
    setName(372, u8"乗ると動くリフト", "One-way Moving Platform");
    setName(373, u8"レール動作の全あたりポリゴン", "Small Gray Block [UNUSED]");
    setName(374, u8"溶岩振り子リフト中央", "Hanging chain holder");
    setName(375, u8"グルグル", "Spinner (Ball 'n' Chain) [UNUSED]");
    setName(376, u8"親子オブジェ・子・城", "Movement-controlled Silver-Gear Block [CRASHES] [UNUSED - NSMBW]");
    setName(377, u8"全当たりポリゴン・開閉", "Solid Opening Block with Light Gem [CRASHES] [UNUSED - NSMBW]");
    setName(378, u8"トーピード基地", "Skull Box (Torpedo Ted Launcher)");
    setName(379, u8"トーピード", "Torpedo Ted");
    setName(380, u8"子ヨッシー用ブロック", "Question Block Containing Baby Yoshi");
    setName(381, u8"中心君対応ファイアーバー", "Pivotal-rotation-controlled Fire Bar [UNUSED]");
    setName(382, u8"ウナボン", "Dragoneel");
    setName(383, u8"ウェンディ", "Wendy O. Koopa");
    setName(384, u8"環境音タグ", "Environmental Sound Effects");
    setName(385, u8"ルドウィッグ", "Ludwig von Koopa");
    setName(386, u8"アクター冷凍コイン", "Meltable Ice Chunk");
    setName(387, u8"サーチトーピード", "Homing Torpedo Ted");
    setName(388, u8"観覧車リフト", "Pink Multi-platform Spinner");
    setName(389, u8"ロイ", "Roy Koopa");
    setName(390, u8"回転ブロック・木", "Pivotal-rotation-controlled Jungle Bridge Platform");
    setName(391, u8"回転ブロック・石", "Pivotal-rotation-controlled Crystal Block (Stone)");
    setName(392, u8"水中クッパJr", "Bowser Jr. (W5) [UNUSED]");
    setName(393, u8"硬い氷ブロック", "3x3 Ice Block");
    setName(394, u8"グループトーピード", "Grouped Torpedo Ted [UNUSED]");
    setName(395, u8"星リフト", "Spinning Star Platform");
    setName(396, u8"葉っぱリフト", "Beanstalk Leaf");
    setName(397, u8"アクター回転制御君用ハテナブロック", "Rotation-controlled Question Block");
    setName(398, u8"アクター回転制御君用レンガブロック", "Rotation-controlled Brick Block");
    setName(399, u8"水中クッパJr", "Bowser Jr. in Clown Car");
    setName(400, u8"ライト付き半当たり回転リフト", "Pivotal-rotation-controlled Lantern Platform");
    setName(401, u8"シャッフルブロックマネージャ", "Minigame Controller - Block Shuffling [UNUSED]");
    setName(402, u8"緑リング", "Green Coin Ring");
    setName(403, u8"イギー", "Iggy Koopa");
    setName(404, u8"OBJ土管・上向きNEXTGOTO", "Pipe - Up (Enterable)");
    setName(405, u8"親子オブジェ・子・組み合わせ", "Movement-controlled Combination Platform [CRASHES] [UNUSED]");
    setName(406, u8"ボスK.K.", "Sumo Bro. Boss");
    setName(407, u8"マリオ床地形アクター", "Bump-from-below Platform");
    setName(408, u8"ミニゲームキノピオ", "Toad");
    setName(409, u8"ワンワン杭", "Chain Chomp");
    setName(410, u8"モノレールブロック", "Ludwig's Castle Platform");
    setName(411, u8"カメック", "Kamek");
    setName(412, u8"カメックデモ管理タグ", "Kamek Cutscene Controller");
    setName(413, u8"シャドウ君", "Nabbit");
    setName(414, u8"レミー飛行船", "Lemmy's Airship in Background");
    setName(415, u8"モートン飛行船", "Morton's Airship in Background");
    setName(416, u8"湧き出しサーチマグナムキラー", "Bull's-Eye Banzai Bill Spawner [UNUSED]");
    setName(417, u8"ラリー飛行船", "Larry's Airship in Background");
    setName(418, u8"ウェンディ飛行船", "Wendy's Airship in Background");
    setName(419, u8"イギー飛行船", "Iggy's Airship in Background");
    setName(420, u8"ロイ飛行船", "Roy's Airship in Background");
    setName(421, u8"ルドウィッグ飛行船", "Ludwig's Airship in Background");
    setName(422, u8"アクター巨大レンガブロック", "Big Brick Block");
    setName(423, u8"ミニゲームマネージャ", "Minigame Controller");
    setName(424, u8"ボス大砲（コクッパ飛行船乗り込み用）", "Pipe Cannon to Airship");
    setName(425, u8"木の枝伸縮リフト", "Beanstalk Tendril");
    setName(426, u8"風船吊るアクター", "Balloon with Goomba or Coin");
    setName(427, u8"水に浮く氷ブロック", "Floating Snowy Box[es]");
    setName(428, u8"モノレールブロックのレール", "Ludwig's Castle Platform Rail");
    setName(429, u8"親子オブジェ・子・互い違い", "Movement-controlled Giant Metal Bar");
    setName(430, u8"親子オブジェ・子・鉄", "Movement-controlled Iron Box [UNUSED]");
    setName(431, u8"親子オブジェ・子・岩", "Movement-controlled Stone Block");
    setName(432, u8"ジュニアデモ管理タグ", "Bowser Jr. Controller");
    setName(433, u8"ボクシングクッパJr.", "Bowser Jr (Clown Car)");
    setName(434, u8"回転ブロック・鉄", "Pivotal-rotation-controlled Metal Block [UNUSED]");
    setName(435, u8"ボスK.K.デモ管理タグ", "Sumo Bro Boss Cutscene Controller");
    setName(436, u8"グループ線キノコブロック", "Grouped Line-controlled Mushroom Block [NEEDS PATCH] [CRASHES] [UNUSED - NSMBW]");
    setName(437, u8"クリボー", "Goomba (duplicate) [UNUSED]");
    setName(438, u8"クリボー", "Goomba (duplicate 2) [UNUSED]");
    setName(439, u8"お化け屋敷の回る部屋", "Ghost House Rotating Room [CRASHES] [UNUSED]");
    setName(440, u8"わきだし火山弾", "Raining Debris");
    setName(441, u8"セイちゃん", "Fliprus");
    setName(442, u8"中間ウナボン", "Dragoneel (Midway)");
    setName(443, u8"ホネメット", "Bony Beetle");
    setName(444, u8"水に浮く氷ブロック（大）", "Giant Floating Snowy Box[es] [UNUSED]");
    setName(445, u8"豆の木", "Big Beanstalk");
    setName(446, u8"雪玉", "Fliprus Snowball");
    setName(447, u8"グループトゲメット", "Grouped Spike Top");
    setName(448, u8"水中クッパJr.用トーピード生成タグ", "Torpedo Ted for Bowser Jr. Fight (W5-Ship)");
    setName(449, u8"宝箱のカギ", "Nothing. [UNUSED]");
    setName(450, u8"カメックツララ配置", "Kamek Block");
    setName(451, u8"クエストアクター配置タグ", "Nabbit Placement");
    setName(452, u8"スロットチビヨッシー", "Slot (minigame) Baby Yoshi [UNUSED]");
    setName(453, u8"マジックハンドパー", "Airship Hand (Hand Form)");
    setName(454, u8"マジックハンドグー", "Airship Hand (Fist Form)");
    setName(455, u8"範囲指定コイン監視拍手君", "Location-based Clapping Controller");
    setName(456, u8"カメックワープ位置", "Kamek Warp - Useless [UNUSED]");
    setName(457, u8"波打つ床地形アクター", "Wobbly Bone Platform");
    setName(458, u8"コインバトル用土管・下向きNEXTGOTO", "Golden Pipe - Down (Enterable)");
    setName(459, u8"W8道中クッパJr", "Bowser Jr. (Clown Car) Controller");
    setName(460, u8"マジックハンドタグパー", "Data for Airship Hand (Hand Form)");
    setName(461, u8"マジックハンドタググー", "Data for Airship Hand (Fist Form)");
    setName(462, u8"クッパ", "Bowser");
    setName(463, u8"ボスクッパスイッチボタン", "Bowser Switch [NEEDS PATCH] [UNUSED]");
    setName(464, u8"クッパ用足場", "Bowser Bridge Piece");
    setName(465, u8"カメックブロック", "Kamek Floor Block");
    setName(466, u8"城クッパデモ管理タグ", "Castle Bowser Cutscene Controller");
    setName(467, u8"クッパシャッター", "Bowser Shutter");
    setName(468, u8"クッパ炎（湧き出し）", "Bowser Fireball");
    setName(469, u8"ピーチ", "Peach");
    setName(470, u8"紫リング", "Red Ring (2) [UNUSED]");
    setName(471, u8"中クリボー", "Medium Goomba");
    setName(472, u8"大クリボー", "Big Goomba");
    setName(473, u8"最終クッパ", "Final Bowser");
    setName(474, u8"コインまき砲台", "Toad House Coin/Bowser/1-Up Cannon");
    setName(475, u8"アクター巨大ハテナブロック", "Big Question Block");
    setName(476, u8"でかノコノコ", "Big Koopa Troopa");
    setName(477, u8"最終クッパJr", "Bowser Jr. - Final Battle");
    setName(478, u8"ボクシングクッパJr.専用床", "Bowser Jr. World 7 Battle Floor Block");
    setName(479, u8"親子オブジェ・子・警告", "Movement-controlled Warning Platform [CRASHES] [UNUSED]");
    setName(480, u8"回転制御用コレクションコイン", "Rotation-controlled Star Coin");
    setName(481, u8"ニセムサ", "Waddlewing");
    setName(482, u8"メカプクプク", "Mecha Cheep");
    setName(483, u8"同期ファイアーバー", "Grouped Fire Bar");
    setName(484, u8"条件フラグ付き回転制御君", "Movement Controller - Rotation (Spinning, Location-triggered)");
    setName(485, u8"親子オブジェ・子・互い違い歯車", "Movement-controlled Giant Metal Bar Gearbox");
    setName(486, u8"フレーム設定タグ", "Darkened Screen Corners Effect (Darkness Frame)");
    setName(487, u8"クッパ専用エリアＯＢＪ", "Bowser Area");
    setName(488, u8"土管ウナボン", "Dragoneel (Specific Entrance)");
    setName(489, u8"飛行船の底", "Airship Segment Spawner");
    setName(490, u8"飛行船の底の枠", "Airship Collar");
    setName(491, u8"W8道中クッパJr.用半当たり上下移動リフト", "Vertically-moving Bone Platform");
    setName(492, u8"W8道中クッパJr.用半当たり左右移動リフト", "Horizontally-moving Bone Platform");
    setName(493, u8"全当たりポリゴン・飛行船", "World 7 Tileset Platform - Follows Screen");
    setName(494, u8"水中クッパJr.退避位置", "Underwater Bowser Jr. Retraction position");
    setName(495, u8"吸い込み水タグ", "Down-Pulling Underwater Bubbles");
    setName(496, u8"アクター重力付コイン", "Coin with Gravity");
    setName(497, u8"最終クッパデモ管理タグ", "Final Bowser Cutscene Controller");
    setName(498, u8"アクターコイン噴水湧き出しタグ", "Fountain Coin Spawner [UNUSED]");
    setName(499, u8"親子オブジェ・子・野原用・半当たり", "Movement-controlled Acorn Plains Semi-solid Land Block");
    setName(500, u8"クッパ電線", "Bowser Amps");
    setName(501, u8"クッパ電線タグ", "Bowser Amp Controller");
    setName(502, u8"クッパ電線単体", "Single Bowser Amp [UNUSED]");
    setName(503, u8"絵画ステージ用ゴールポール", "Painted Goal Pole");
    setName(504, u8"ゴロゴロ", "Grrrol");
    setName(505, u8"ゴロゴロ（巨大）", "Big Grrrol");
    setName(506, u8"チャレンジモード専用ブロック", "Challenge-mode-only Solid Block");
    setName(507, u8"流れ星スター", "Super Star Spawner [UNUSED]");
    setName(508, u8"乗ると動くリフト空用", "Cloud Platform");
    setName(509, u8"OBJ土管・右向きNEXTGOTO", "Pipe - Right (Enterable) [UNUSED]");
    setName(510, u8"OBJ土管・左向きNEXTGOTO", "Pipe - Left (Enterable) [UNUSED]");
    setName(511, u8"OBJ土管・下向きNEXTGOTO", "Pipe - Down (Enterable)");
    setName(512, u8"回転ブロック・お化け屋敷の沈没船", "Pivotal-rotation-controlled Ghost Ship Block");
    setName(513, u8"土管ジョイント描画", "Pipe Joint");
    setName(514, u8"土管ジョイントマメ描画", "Mini Pipe Joint");
    setName(515, u8"親子オブジェ・子・溶岩城", "Movement-controlled Lava Castle Platform");
    setName(516, u8"マメマリオ用OBJ土管(右)", "Mini Pipe - Right");
    setName(517, u8"マメマリオ用OBJ土管(左)", "Mini Pipe - Left");
    setName(518, u8"マメマリオ用OBJ土管(上)", "Mini Pipe - Up");
    setName(519, u8"マメマリオ用OBJ土管(下)", "Mini Pipe - Down");
    setName(520, u8"ボスクッパ斧付スイッチボタン", "Bowser Switch with Axe");
    setName(521, u8"ゴールキノコハウス描画", "Goal Mushroom House [CRASHES] [UNUSED]");
    setName(522, u8"浮き樽", "Floating Barrel [CRASHES] [UNUSED - NSMBW]");
    setName(523, u8"敵コース用アクターパタブロック", "Flying Question Block Generator - Ambush");
    setName(524, u8"親子オブジェ・子・砦岩", "Movement-controlled Tower Rock Block");
    setName(525, u8"画面追従ハテナブロック", "Screen-following Question Block");
    setName(526, u8"画面追従レンガブロック", "Screen-following Brick Block");
    setName(527, u8"ピーチデモ管理タグ", "Peach Ending Cutscene Controller");
    setName(528, u8"全水中エフェクトフィルター", "Underwater Effect Filter");
    setName(529, u8"クロスケー", "Crowber [CRASHES] [UNUSED - NSMBW]");
    setName(530, u8"ねじ回しで動く全当たり OBJ・子・ピラミッド", "Bolt-controlled Stone Block");
    setName(531, u8"泡", "Bubble Effect Generator");
    setName(532, u8"ロイ用湧き出しリフト", "Roy Battle Platform Controller");
    setName(533, u8"ウェンディのツララ", "Icicle - Wendy Battle");
    setName(534, u8"同期半当たり左右移動リフト", "Grouped Horizontally-moving Platform");
    setName(535, u8"同期半当たり上下移動リフト", "Grouped Vertically-moving Platform");
    setName(536, u8"マンホールプー", "Rocky Wrench");
    setName(537, u8"スパナ", "Flying Wrench [UNUSED]");
    setName(538, u8"クッキー", "Roto-Disc [CRASHES] [UNUSED]");
    setName(539, u8"ガッタン", "Rolling Ice Block [UNUSED]");
    setName(540, u8"フライングキノコ", "Flying Mushroom Platform [UNUSED]");
    setName(541, u8"フライングキノコ(湧き出し)", "Flying Mushroom Platform Spawner [UNUSED]");
    setName(542, u8"キノコ足場・左右移動", "Bouncy Mushroom Platform (Horizontal) [UNUSED]");
    setName(543, u8"クエスト用キノピオ", "Toad (for Treasure Chests) [UNUSED]");
    setName(544, u8"カラーキノコリフト", "Moving Mushroom Platform");
    setName(545, u8"湧き出しバクバク", "Cheep Chomp Generator");
    setName(546, u8"追従草花", "Grass/Flowers");
    setName(547, u8"クエストの景品アイテム", "Treasure Chest Prize Item [UNUSED]");
    setName(548, u8"光で現れるブロック", "\"Block that appears in the light\" [UNUSED]");
    setName(549, u8"親子オブジェ・子・砂漠の遺跡", "Movement-controlled Desert Ruins Block");
    setName(550, u8"でか土管パックンフラワー", "Giant Pipe Piranha Plant");
    setName(551, u8"マジックハンド・水中クッパJr.デモ用", "Nothing. [UNUSED]");
    setName(552, u8"ブラックパックンOBJ", "Moving Tiltable Muncher (Two-Way)");
    setName(553, u8"進行方向切換リフト", "4-part Steerable Platform [UNUSED]");
    setName(554, u8"ムササビプレイヤー参照タグ", "Location-based button hint");
    setName(555, u8"玉乗りリフト", "Ball-Riding Lift [CRASHES] [UNUSED - NSMBW]");
    setName(556, u8"チビヨッシー（泡）（スタッフロール）", "Credits Bubble Baby Yoshi [CRASHES]");
    setName(557, u8"スタッフロールマネージャ", "Credits Controller");
    setName(558, u8"W8道中クッパJr.管理タグ", "Bowser Jr. in Flying Clown Car");
    setName(559, u8"シャドウ君退避タグ", "Nabbit Refuge Location");
    setName(560, u8"ウェンディの床", "Wendy Battle Floor");
    setName(561, u8"シャドウ君の家の読むタグ", "Records Toad House Signboard");
    setName(562, u8"全当たりポリゴン・高原用", "Sky Tileset Platform [UNUSED]");
    setName(563, u8"親子オブジェ・子・高原用", "Movement-controlled Highland Platform [UNUSED]");
    setName(564, u8"草花種類指定タグ", "Flower/Grass Type Setter");
    setName(565, u8"ウーチャン", "Magmaw");
    setName(566, u8"クエスト専用ブロック", "Nabbit-Chase-Only Metal Block");
    setName(567, u8"湧き出しケロンパ", "Flame Chomp Spawner [UNUSED]");
    setName(568, u8"ウナボン(復活)", "Eel - Midway");
    setName(569, u8"クエスト用デモロケーションタグ", "Nabbit Reward");
    setName(570, u8"ショートプレイ結果デモタグ", "Short Play Results Controller");
    setName(571, u8"ショートプレイ結果画面のピーチ姫", "Peach [UNUSED]");
    setName(572, u8"ＤＶ草花発生", "CRASHING SPRITE [UNUSED]");
    setName(573, u8"同期線リフト", "Grouped Platform - Uses Lines");
    setName(574, u8"コインバトル用土管・上向きNEXTGOTO", "Golden Pipe - Up (Enterable)");
    setName(575, u8"OBJ土管(左・グループ)", "Pipe - Left (Grouped, Solid) [UNUSED]");
    setName(576, u8"OBJ土管(右・グループ)", "Pipe - Right (Grouped, Solid) [UNUSED]");
    setName(577, u8"OBJ土管(上・グループ)", "Pipe - Up (Grouped, Solid) [UNUSED]");
    setName(578, u8"OBJ土管(下・グループ)", "Pipe - Down (Grouped, Solid) [UNUSED]");
    setName(579, u8"ロックガボン", "Stone Spike");
    setName(580, u8"ロックガボン（常駐）", "Stone Spike (Stationary)");
    setName(581, u8"サーチキラー砲台", "Bull's-Eye Bill Blaster (Homing, Missile) (+) [UNUSED]");
    setName(582, u8"サーチマグナムキラー砲台", "Bull's-Eye Banzai Bill Blaster (Homing, Missile) (+) [UNUSED]");
    setName(583, u8"サーチマグナムキラー砲台（下向き）", "Upside-Down Bull's-Eye Banzai Bill Blaster (Homing, Missile) (+) [UNUSED]");
    setName(584, u8"鉄箱", "Metal Box");
    setName(585, u8"鉄箱(湧き出し)", "Metal Box Generator");
    setName(586, u8"飛びメカプク(湧き出し)", "Flying Mecha Cheep Spawner [UNUSED]");
    setName(587, u8"飛びメカプク", "Flying Mecha Cheep [UNUSED]");
    setName(588, u8"サーチプクプク", "Deep Cheep");
    setName(589, u8"サーチプクプク（中）", "Medium Deep Cheep");
    setName(590, u8"にげプクプク", "Eep Cheep");
    setName(591, u8"にげプクプク（中）", "Medium Eep Cheep");
    setName(592, u8"サーチプクプク(湧き出し)", "Searching Cheep Cheep [UNUSED]");
    setName(593, u8"K.K.", "Sumo Bro.");
    setName(594, u8"K.K.の雷", "Sumo. Bro's Lightning");
    setName(595, u8"カキボー", "Goombrat");
    setName(596, u8"サーチトーピード基地", "Red Skull Box (Targeting Ted Launcher)");
    setName(597, u8"にげプクプク(湧き出し)", "Eep Cheep Spawner [UNUSED]");
    setName(598, u8"お題モード足場", "Disappear-when-off Platform / Coin Edit No-Coin Area (Doesn't Use Locations)");
    setName(599, u8"ゴールリング", "Goal Ring");
    setName(600, u8"DRC画面にしか見えないブロック", "3-Up Moon Block");
    setName(601, u8"敵コースデモ用シャドウ君", "Nabbit for Enemy Course Demo (?) [UNUSED]");
    setName(602, u8"つかまり鎖", "Swinging Chain");
    setName(603, u8"毒霧", "Approaching Death Cloud");
    setName(604, u8"戦闘後デモボクシングクッパJr.", "Bowser Jr. for After-Combat Demo (World 7) (?)");
    setName(605, u8"戦闘後デモボクシングクッパJr.のクラウン", "Clown Car for After-Combat Demo (Bowser Jr. W7) [UNUSED]");
    setName(606, u8"こでかメット", "Big Buzzy Beetle");
    setName(607, u8"グループコレクションコイン線対応", "Grouped Star Coin - Uses Lines [UNUSED]");
    setName(608, u8"タッチ無効アクター", "No-boost-block Location");
    setName(609, u8"イギー部屋", "Iggy Room");
    setName(610, u8"ショートプレイ結果デモタグ", "Title screen controller");
    setName(611, u8"クエスト用キノピオ", "Giant Wiggler Spawner");
    setName(612, u8"Ｐムササビブロック", "Non-solid-when-you-have-P-Acorn Block");
    setName(613, u8"コインバトル用土管・左向きNEXTGOTO", "Golden Pipe - Left (Enterable) [UNUSED]");
    setName(614, u8"コインバトル用土管・右向きNEXTGOTO", "Golden Pipe - Right (Enterable) [UNUSED]");
    setName(615, u8"グループプクプク", "Grouped Cheep Cheep");
    setName(616, u8"グループプクプク管理タグ", "Cheep Cheep Group Controller");
    setName(617, u8"シャボン保護地帯タグ", "\"Tags bubble protection zone\"");
    setName(618, u8"アクター壊れないブロック", "Steel Block");
    setName(619, u8"アクター木ブロック", "Wooden Block");
    setName(620, u8"でかフグマンネン", "Big Porcupuffer [CRASHES] [UNUSED]");
    setName(621, u8"でかフグマンネン(湧き出し)", "Big Porcupuffer Spawn Area [CRASHES] [UNUSED]");
    setName(622, u8"エディットコインアクター設置範囲タグ", "Coin Edit No-coin Area (Uses Locations)");
    setName(623, u8"境界速度調整君", "Boundary Speed Adjustor");
    setName(624, u8"グループＩＤトゲメット用", "Spike Top Group Controller");
    setName(625, u8"ねじ回しで動く全当たり OBJ・子・ピラミッド・常駐", "Stationary Bolt-controlled Stone Block");
    setName(626, u8"K.K.(常駐)", "Stationary Sumo Bro. - NSLU");
    setName(627, u8"W8道中クッパJr.用半アタリ移動リフト（親子オブジェ対応）", "Movement-controlled Bone Platform - NSLU");
    setName(628, u8"マジックハンドタググー・速い", "Data for Airship Hand (\"Fast\" form) - NSLU [UNUSED]");
    setName(629, u8"湧き出しジュゲム(マルチプレイ用)", "Lakitu Spawn Location - NSLU");
    setName(630, u8"ゴールポール(RDash)", "Goal Pole - NSLU");
    setName(631, u8"絵画ステージ用ゴールポール(RDash)", "Painted Goal Pole - NSLU");
    setName(632, u8"シーソーリフト(RDash)", "Seesaw Blue Mushroom Platform - NSLU");
    setName(633, u8"リモコン上昇定員リフト(RDash)", "Tilt-controlled Moving Platform - NSLU");
    setName(634, u8"RDashルイージブロック", "Super Guide Block - NSLU");
    setName(635, u8"城のドア(RDash用)", "Castle Boss Door - NSLU");
    setName(636, u8"砦のドア(RDash用)", "Tower Boss Door - NSLU");
    setName(637, u8"クッパドア(RDash用)", "Bowser Boss Door - NSLU");
    setName(638, u8"ウナボン(RDash)", "Dragoneel - NSLU");
    setName(639, u8"土管NextGotoタイマー加算タグ", "Time Bonus - NSLU");
    setName(640, u8"RDash用ケロンパ", "Flame Chomp - NSLU");
    setName(641, u8"ワンワン杭(RDash)", "Chain Chomp - NSLU");
    setName(642, u8"親子オブジェ・親(R-Dash専用版)", "Movement Controller - Two-Way - NSLU");
    setName(643, u8"バブル(RDash)", "Lava Bubble - NSLU");
    setName(644, u8"同期バブル(RDash)", "Grouped Lava Bubble - NSLU");
    setName(645, u8"回転ブロック・木(RDash)", "Pivotal-rotation-controlled Jungle Bridge Platform - NSLU");
    setName(646, u8"マグナムキラー砲台(RDash)", "Banzai Bill Blaster with Luigi Emblem - NSLU (+)");
    setName(647, u8"マグナムキラー砲台（下向き）(RDash)", "Upside-Down Banzai Bill Blaster with Luigi Emblem - NSLU (+) [UNUSED]");
    setName(648, u8"サーチマグナムキラー砲台(RDash)", "Bull's-Eye Banzai Bill Blaster with Luigi Emblem - NSLU (+) [UNUSED]");
    setName(649, u8"サーチマグナムキラー砲台（下向き）(RDash)", "Upside-Down Bull's-Eye Banzai Bill Blaster with Luigi Emblem - NSLU (+) [UNUSED]");
    setName(650, u8"コレクション親制御(RDash)", "Movement-controlled Star Coin - NSLU");
    setName(651, u8"ガボン(RDash)", "Spike - NSLU");
    setName(652, u8"パタメット", "Para-Beetle - NSLU");
    setName(653, u8"キングキラー(RDash)", "King Bill - NSLU");
    setName(654, u8"タイトルデモ用シャドウ君", "Running Nabbit - NSLU [UNUSED]");
    setName(655, u8"スネークブロック(RDash用)", "Snake Block - NSLU");
    setName(656, u8"ズーム君(RDash)", "Horizontal Scroll Limit (Left) - NSLU");
    setName(657, u8"ピーチデモ用シャドウ君", "Nabbit for Peach Demo (?) - NSLU [UNUSED]");
    setName(658, u8"線リフトRDash", "Platform - Uses Lines - NSLU");
    setName(659, u8"ゴロゴロ（巨大RDash）", "Big Grrrol - NSLU");
    setName(660, u8"フラグスイッチ条件フラグＲＤＡＳＨ用", "Event Controller - LOCATION (Location-State-Triggered) - NSLU [UNUSED]");
    setName(661, u8"K.K.(リフト修正版)", "Sumo Bro - NSLU [UNUSED]");
    setName(662, u8"青リング", "Blue Ring - NSLU");
    setName(663, u8"アクターコインＲＤＡＳＨ用", "Coin - NSLU");
    setName(664, u8"ウナボン(復活RDash)", "Sun Gleam & Bubble Underwater Effect - NSLU");
    setName(665, u8"コレクション親制御(RDash生成範囲拡張版)", "Movement-controlled Star Coin - NSLU - Wider spawn range");
    setName(666, u8"マジックハンドグー(RDash)", "Airship Bottom - NSLU");
    setName(667, u8"土管大砲(RDash)", "Pipe Cannon - NSLU");
    setName(668, u8"飛行船の底(RDash)", "Airship Hand - NSLU");
    setName(669, u8"親子オブジェ・子・砦岩(RDash用)", "Movement-controlled Tower Rock Block - NSLU");
    setName(670, u8"ミニゲームマネージャ(RDash)", "Minigame Manager - NSLU [UNUSED]");
    setName(671, u8"トゲ鉄球通り穴(RDash用2砦)", "Grrrol Passage - NSLU");
    setName(672, u8"レールエフェクト発生ブロック", "Movement Controller - Brick Blocks - NSLU");
    setName(673, u8"書き換えブロック(RDash用)", "Tile God - NSLU");
    setName(674, u8"溶岩地面(RDash)", "Lava Land Block - NSLU");
    setName(675, u8"歯車(RDash)", "Rotating Stone Gear - NSLU");
    setName(676, u8"溶岩振り子リフト(RDash)", "Pivotal-rotation-controlled Castle Platform - NSLU");
    setName(677, u8"全水中エフェクトフィルター(RDash)", "Underwater Effect Filter - NSLU");
    setName(678, u8"アクター透明ブロックRDash", "Event-activated Invisible Item Block - NSLU");
    setName(679, u8"回転土管(RDash)", "Pivotal-rotation-controlled Pipe - NSLU");
    setName(680, u8"RDash5-5専用モアイ", "Stone-Eye - NSLU");
    setName(681, u8"看板矢印(RDash)", "Arrow Signboard - NSLU");
    setName(682, u8"水面パックン(RDash)", "River Piranha Plant - NSLU");
    setName(683, u8"アクターハテナブロック(RDash)", "Question Block - NSLU");
    setName(684, u8"ハイパーマックス上君（左）", "Scroll Limit - NSLU");
    setName(685, u8"ハイパーマックス上君（右）", "Vertical Scroll Limit (Up) - NSLU");
    setName(686, u8"スイッチＰボタン(RDash)", "Event Controller - \"P\" Switch (Blue) - NSLU");
    setName(687, u8"パラボム兵(RDash)", "Para-Bomb - NSLU");
    setName(688, u8"鉄箱(RDash)", "Metal Box - NSLU");
    setName(689, u8"スタッフロールマネージャ", "Credits Controller - NSLU [UNUSED]");
    setName(690, u8"ルイージ看板（１−１）", "Luigi Signboard (1-1, NSLU Logo)");
    setName(691, u8"ルイージ看板（９−９）", "Luigi Signboard (9-9, \"THANK YOU!!\" Sign)");
    setName(692, u8"アクターレンガブロック(RDash)", "Brick Block - NSLU");
    setName(693, u8"中心君対応グルグル(RDash)", "Pivotal-rotation-controlled Pendulum (Spinner, Ball 'n' Chain) - NSLU");
    setName(694, u8"専用お化け屋敷の全当たりポリゴン", "Ghost House Platform - NSLU [UNUSED]");
    setName(695, u8"ウニラ(RDash用)", "Urchin - NSLU");
    setName(696, u8"回転ブロック・お化け(RD4-化け専用)", "Ghost House Box (Pivotal-rotation-controlled / Path-controlled) - NSLU");
    setName(697, u8"鉄箱(RDash-生成範囲狭い版)", "Metal Box - NSLU - Narrower spawn range");
    setName(698, u8"地面パックンフラワー(RDash)", "Grounded Piranha Plant - NSLU");
    setName(699, u8"慣性線リフト親(RDash)", "Spine Coaster - NSLU");
    setName(700, u8"慣性線リフト子(RDash)", "Spine Coaster (2) - NSLU");
    setName(701, u8"アクターレンガブロック（レール縦方向）", "Path-controlled Brick Block (Vertical)");
    setName(702, u8"ハナチャン", "Wiggler - NSLU");
    setName(703, u8"回転拡縮テレサRDash（親）", "Boo Circle - NSLU");
    setName(704, u8"アクター回転制御レンガブロック(RDash)", "Brick Block (2) - NSLU");
    setName(705, u8"RD3-3専用常駐間欠泉(水)", "Location-triggered Water Geyser - NSLU 3-3");
    setName(706, u8"回転制御レンガブロック(R99)", "Pivotal-rotation-controlled Brick Block - NSLU 9-9");
    setName(707, u8"アクター回転制御ハテナブロック(R99)", "Pivotal-rotation-controlled Question Block - NSLU 9-9");
    setName(708, u8"プレイヤー画面横挟み要求タグ", "Autoscrolling Player Effect (?)- NSLU");
    setName(709, u8"回転ブロック・鉄(RDASH用)", "Pivotal-rotation-controlled Metal Block - NSLU");
    setName(710, u8"スイッチＰボタン(壁キック無効版)", "Event Controller - \"P\" Switch (Blue) - Not Wall-kickable");
    setName(711, u8"回転ブロック・鉄(RDASH用その2)", "Metal Block Platform - NSLU");
    setName(712, u8"地面パックンフラワー(R33)", "Grounded Piranha Plant - NSLU [UNUSED]");
    setName(713, u8"ウニラ・RDASH・BGチェック狭い版", "Urchin (2) - NSLU");
    setName(714, u8"逆振り子リフト(RDash当たり消えない版)", "Pivotal-rotation-controlled Scaffold Platform - NSLU (Permanent)");
    setName(715, u8"フラグスイッチ条件フラグＲ６３用", "Event Controller - LOCATION (Location-State-Triggered) - NSLU 6-3");
    setName(716, u8"キリフキー(RDash)", "Foo - NSLU");
    setName(717, u8"スネークブロック(R76用)", "Snake Block - NSLU 7-6");
    setName(718, u8"シャドウ君の家の読むタグ", "Player-Looks-At-Screen Toggle - NSLU");
    setName(719, u8"RDash2-4専用モアイ", "Giant Tilted Path-controlled Stone-Eye - NSLU");
    setName(720, u8"RDash2-4専用モアイ（下向き）", "Tilted Path-controlled Stone-Eye - NSLU");
    setName(721, u8"コレクション親制御(R６城)", "Falling Star Coin (?) - NSLU");
    setName(722, u8"看板矢印(生成範囲狭い版)", "Arrow Signboard - Narrower spawn range");
    setName(723, u8"グループプクプク（中）", "Medium-sized Grouped Cheep Cheep");

    // -------------------------------------------------------------

    setActorFactory<Kuribo>(0);

    setActorFactory<Nokonoko>(19);

    setActorFactory<GoalPole>(31);

    setActorFactory<CollectionCoin>(45);

    setActorFactory<CollectionCoin>(47);

    setActorFactory<Nokonoko>(55);

    setActorFactory<ActorBlockHatena>(59);
    setActorFactory<ActorBlockRenga>(60);

    setActorFactory<ActorCoin>(65);
    setActorFactory<ActorCoin>(66);

    setActorFactory<ObjDokanActorUp>(139);
    setActorFactory<ObjDokanActorDown>(140);
    setActorFactory<ObjDokanActorLeft>(141);
    setActorFactory<ObjDokanActorRight>(142);

    setActorFactory<ActorBlockHatena>(147);
    setActorFactory<ActorBlockRenga>(148);
    setActorFactory<ActorCoin>(149);

    setActorFactory<ActorBlockHatena>(205);

    setActorFactory<ActorBlockHatena>(233);
    setActorFactory<ActorBlockRenga>(234);

    setActorFactory<ActorCoin>(279);

    setActorFactory<ActorCoin>(325);

    setActorFactory<ActorCoin>(328);

    setActorFactory<ActorBlockHatena>(397);
    setActorFactory<ActorBlockRenga>(398);

    setActorFactory<ObjDokanActorUpNextGoto>(404);

    setActorFactory<ActorBlockBigRenga>(422);

    setActorFactory<Kuribo>(437);
    setActorFactory<Kuribo>(438);

    setActorFactory<ActorBlockBigHatena>(475);
    setActorFactory<Nokonoko>(476);

    setActorFactory<CollectionCoin>(480);

    setActorFactory<ActorCoin>(496);

    setActorFactory<GoalPole>(503);

    setActorFactory<ObjDokanActorRightNextGoto>(509);
    setActorFactory<ObjDokanActorLeftNextGoto>(510);
    setActorFactory<ObjDokanActorDownNextGoto>(511);

    setActorFactory<DokanJoint>(513);

    setActorFactory<ActorBlockHatena>(525);
    setActorFactory<ActorBlockRenga>(526);

    setActorFactory<ObjDokanActorLeft>(575);
    setActorFactory<ObjDokanActorRight>(576);
    setActorFactory<ObjDokanActorUp>(577);
    setActorFactory<ObjDokanActorDown>(578);

    setActorFactory<Kuribo>(595);

    setActorFactory<GoalPole>(630);
    setActorFactory<GoalPole>(631);

    setActorFactory<ActorCoin>(663);

    setActorFactory<ActorBlockHatena>(683);

    setActorFactory<ActorBlockRenga>(692);

    setActorFactory<ActorBlockRenga>(701);

    setActorFactory<ActorBlockRenga>(704);
}

ActorCreateMgr::~ActorCreateMgr()
{
}

void ActorCreateMgr::setTypeMaxNum(u16 max_num)
{
    RIO_ASSERT(max_num >= mTypeMaxNum); // Can only go up, for now

    const u16 old_max_num = mTypeMaxNum;
    mTypeMaxNum = max_num;

    // Give every valid type an entry, so that a type which never receives a name still has a non-empty, unique label to use as an ImGui ID.
    for (u16 type = old_max_num; type < max_num; type++)
    {
        NameEntry& entry = mMapActorNameMap[type];
        entry.flags = NAME_FLAG_NONE;
        updateNameEntry_(type, entry);
    }
}

u16 ActorCreateMgr::getTypeMaxNum() const
{
    return mTypeMaxNum;
}

namespace {

bool containsNoCase(std::string_view haystack, std::string_view needle)
{
    if (needle.size() > haystack.size())
        return false;

    const size_t limit = haystack.size() - needle.size();
    for (size_t i = 0; i <= limit; i++)
    {
        size_t j = 0;
        for (; j < needle.size(); j++)
        {
            const char a = haystack[i + j];
            const char b = needle[j];
            const char a_upper = (a >= 'a' && a <= 'z') ? char(a - 'a' + 'A') : a;
            const char b_upper = (b >= 'a' && b <= 'z') ? char(b - 'a' + 'A') : b;
            if (a_upper != b_upper)
                break;
        }
        if (j == needle.size())
            return true;
    }
    return false;
}

std::string toString(std::u8string_view sv)
{
    return std::string(reinterpret_cast<const char*>(sv.data()), sv.size());
}

}

ActorCreateMgr::NameFlag ActorCreateMgr::deriveNameFlags_(std::string_view name_english)
{
    NameFlag flags = NAME_FLAG_NONE;

    if (containsNoCase(name_english, "UNUSED"))
        flags |= NAME_FLAG_UNUSED;

    if (containsNoCase(name_english, "CRASH"))
        flags |= NAME_FLAG_CRASHES;

    if (containsNoCase(name_english, "NSLU"))
        flags |= NAME_FLAG_NSLU;

    return flags;
}

void ActorCreateMgr::setName(u16 map_actor_type, std::u8string_view name_japanese, std::string_view name_english)
{
    RIO_ASSERT(map_actor_type < mTypeMaxNum);

    NameEntry& entry = mMapActorNameMap[map_actor_type];
    entry.japanese = toString(name_japanese);
    entry.english.assign(name_english);
    entry.flags = deriveNameFlags_(entry.english);

    updateNameEntry_(map_actor_type, entry);
}

void ActorCreateMgr::updateNameEntry_(u16 map_actor_type, NameEntry& entry) const
{
    const std::string& english = entry.english;
    const std::string& japanese = entry.japanese;

    switch (mNameLanguage)
    {
    case ACTOR_NAME_LANGUAGE_JAPANESE:
        entry.display = japanese.empty() ? english : japanese;
        break;

    case ACTOR_NAME_LANGUAGE_BOTH:
        if (english.empty() || japanese.empty())
            entry.display = english.empty() ? japanese : english;
        else
            entry.display = english + " (" + japanese + ")";
        break;

    case ACTOR_NAME_LANGUAGE_ENGLISH:
    default:
        entry.display = english.empty() ? japanese : english;
        break;
    }

    const std::string number = std::to_string(map_actor_type);

    entry.label = entry.display.empty() ? number : number + ": " + entry.display;

    // Always both languages, so search is independent of what is displayed.
    entry.search = number;
    if (!english.empty())
        entry.search += " " + english;
    if (!japanese.empty())
        entry.search += " " + japanese;
}

void ActorCreateMgr::updateNameEntries_()
{
    for (auto& pair : mMapActorNameMap)
        updateNameEntry_(pair.first, pair.second);
}

void ActorCreateMgr::setNameLanguage(ActorNameLanguage language)
{
    RIO_ASSERT(language >= 0 && language < ACTOR_NAME_LANGUAGE_MAX_NUM);

    if (mNameLanguage == language)
        return;

    mNameLanguage = language;
    updateNameEntries_();
}

const ActorCreateMgr::NameEntry* ActorCreateMgr::findNameEntry_(u16 map_actor_type) const
{
    const auto& itr = mMapActorNameMap.find(map_actor_type);
    if (itr != mMapActorNameMap.end())
        return &itr->second;

    return nullptr;
}

const std::string& ActorCreateMgr::getName(u16 map_actor_type) const
{
    static const std::string empty;

    const NameEntry* entry = findNameEntry_(map_actor_type);
    return entry ? entry->display : empty;
}

const std::string& ActorCreateMgr::getNameJapanese(u16 map_actor_type) const
{
    static const std::string empty;

    const NameEntry* entry = findNameEntry_(map_actor_type);
    return entry ? entry->japanese : empty;
}

const std::string& ActorCreateMgr::getNameEnglish(u16 map_actor_type) const
{
    static const std::string empty;

    const NameEntry* entry = findNameEntry_(map_actor_type);
    return entry ? entry->english : empty;
}

const std::string& ActorCreateMgr::getLabel(u16 map_actor_type) const
{
    static const std::string empty;

    const NameEntry* entry = findNameEntry_(map_actor_type);
    return entry ? entry->label : empty;
}

const std::string& ActorCreateMgr::getSearchKey(u16 map_actor_type) const
{
    static const std::string empty;

    const NameEntry* entry = findNameEntry_(map_actor_type);
    return entry ? entry->search : empty;
}

ActorCreateMgr::NameFlag ActorCreateMgr::getNameFlags(u16 map_actor_type) const
{
    const NameEntry* entry = findNameEntry_(map_actor_type);
    return entry ? entry->flags : NAME_FLAG_NONE;
}

void ActorCreateMgr::setActorFactory(u16 map_actor_type, ActorFactory factory, const MapActorData* default_data)
{
    RIO_ASSERT(map_actor_type < mTypeMaxNum);
    mActorFactoryMap[map_actor_type] = std::pair { factory, default_data };
}

const std::pair<ActorFactory, const MapActorData*>* ActorCreateMgr::getActorFactory(u16 map_actor_type) const
{
    const auto& itr = mActorFactoryMap.find(map_actor_type);
    if (itr != mActorFactoryMap.end())
        return &itr->second;

    return nullptr;
}

std::unique_ptr<MapActorItem> ActorCreateMgr::create(const MapActorData& map_actor_data, u32 index) const
{
    const auto& itr = mActorFactoryMap.find(map_actor_data.type);
    if (itr != mActorFactoryMap.end())
        return (*itr->second.first)(map_actor_data, index);

    return std::make_unique<MapActorItem>(map_actor_data, index);
}
