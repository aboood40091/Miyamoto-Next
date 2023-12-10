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
    mMaxID = 0;

    // -------------------------------------------------------------

    setMaxID(724);

    // -------------------------------------------------------------

    setName(  0, u8"クリボー");
    setName(  1, u8"パタクリボー");
    setName(  2, u8"上向き土管パックンフラワー");
    setName(  3, u8"下向き土管パックンフラワー");
    setName(  4, u8"左向き土管パックンフラワー");
    setName(  5, u8"右向き土管パックンフラワー");
    setName(  6, u8"上向き土管ファイヤパックンフラワー");
    setName(  7, u8"下向き土管ファイヤパックンフラワー");
    setName(  8, u8"左向き土管ファイヤパックンフラワー");
    setName(  9, u8"右向き土管ファイヤパックンフラワー");
    setName( 10, u8"上向き土管アイスパックンフラワー");
    setName( 11, u8"下向き土管アイスパックンフラワー");
    setName( 12, u8"左向き土管アイスパックンフラワー");
    setName( 13, u8"右向き土管アイスパックンフラワー");
    setName( 14, u8"地面パックンフラワー");
    setName( 15, u8"地面ファイヤーパックンフラワー");
    setName( 16, u8"地面アイスパックンフラワー");
    setName( 17, u8"地面大パックンフラワー");
    setName( 18, u8"地面ファイヤ大パックンフラワー");
    setName( 19, u8"ノコノコ");
    setName( 20, u8"パタパタ");
    setName( 21, u8"グループパタパタ");
    setName( 22, u8"メット");
    setName( 23, u8"トゲゾー");
    setName( 24, u8"逆さトゲゾー");
    setName( 25, u8"中間ポイントの旗");
    setName( 26, u8"ズーム君");
    setName( 27, u8"マックス上君（左）");
    setName( 28, u8"マックス上君（右）");
    setName( 29, u8"右ストップ君（上）");
    setName( 30, u8"右ストップ君（下）");
    setName( 31, u8"ゴールポール");
    setName( 32, u8"看板矢印");
    setName( 33, u8"ゴロゴロ");
    setName( 34, u8"ゴロゴロ（巨大）");
    setName( 35, u8"ワカメ");
    setName( 36, u8"フラグスイッチタグ");
    setName( 37, u8"フラグスイッチ４スイッチ監視ＡＮＤ");
    setName( 38, u8"フラグスイッチ４スイッチ監視ＯＲ");
    setName( 39, u8"フラグスイッチランダム");
    setName( 40, u8"フラグスイッチ変化スイッチ");
    setName( 41, u8"フラグスイッチ条件フラグ");
    setName( 42, u8"フラグスイッチ連続ＯＮフラグ");
    setName( 43, u8"フラグスイッチ一定周期ＯＮ、ＯＦＦフラグ");
    setName( 44, u8"赤リング");
    setName( 45, u8"コレクションコイン");
    setName( 46, u8"コレクションコイン線対応");
    setName( 47, u8"コレクションコインボルト対応");
    setName( 48, u8"コレクション親制御");
    setName( 49, u8"赤コイン");
    setName( 50, u8"緑コイン");
    setName( 51, u8"チョロプー");
    setName( 52, u8"トゲ鉄球通り穴");
    setName( 53, u8"フグマンネン");
    setName( 54, u8"木の実");
    setName( 55, u8"ノコノコ横方向生成");
    setName( 56, u8"フグマンネン(湧き出し)");
    setName( 57, u8"フィッシュボーン");
    setName( 58, u8"ゴロゴロ");
    setName( 59, u8"アクターハテナブロック");
    setName( 60, u8"アクターレンガブロック");
    setName( 61, u8"アクター透明ブロック");
    setName( 62, u8"中心君対応土管パックンフラワー（上）");
    setName( 63, u8"歩くパックン");
    setName( 64, u8"水面パックン");
    setName( 65, u8"アクターコイン");
    setName( 66, u8"アクターポリゴン追従コイン");
    setName( 67, u8"バサバサ");
    setName( 68, u8"中心君・振り子");
    setName( 69, u8"中心君・回転");
    setName( 70, u8"親子オブジェ・親");
    setName( 71, u8"親子オブジェ・子");
    setName( 72, u8"親子オブジェ・子・野原用");
    setName( 73, u8"アクターコイン湧き出し");
    setName( 74, u8"カニボー");
    setName( 75, u8"アイスブロス");
    setName( 76, u8"ハンマーブロス");
    setName( 77, u8"メガブロス");
    setName( 78, u8"ブーメランブロス");
    setName( 79, u8"ファイアブロス");
    setName( 80, u8"全当たりポリゴン");
    setName( 81, u8"全当たりポリゴン・野原用");
    setName( 82, u8"中心君対応土管パックンフラワー（下）");
    setName( 83, u8"中心君対応土管パックンフラワー（左）");
    setName( 84, u8"中心君対応土管パックンフラワー（右）");
    setName( 85, u8"ケロンパ");
    setName( 86, u8"ウニラ");
    setName( 87, u8"アクター回転制御コイン");
    setName( 88, u8"水地形アクター");
    setName( 89, u8"溶岩地形アクター");
    setName( 90, u8"毒沼地形アクター");
    setName( 91, u8"砂漠地形アクター");
    setName( 92, u8"雲地形アクター");
    setName( 93, u8"靄地形アクター");
    setName( 94, u8"トランポリン雲");
    setName( 95, u8"トランポリン雲(乗ると動く)");
    setName( 96, u8"松明の炎");
    setName( 97, u8"ＢＧ中心くん");
    setName( 98, u8"土管湧き出し敵");
    setName( 99, u8"でかウニラ");
    setName(100, u8"レール動作の全あたりポリゴン・親");
    setName(101, u8"プクプク");
    setName(102, u8"環境現象くん");
    setName(103, u8"回転キラー砲台");
    setName(104, u8"スイッチはてなボタン");
    setName(105, u8"スイッチＰボタン");
    setName(106, u8"プクプク(湧き出し)");
    setName(107, u8"普通のドア");
    setName(108, u8"お化け屋敷のドア");
    setName(109, u8"砦のドア");
    setName(110, u8"城のドア");
    setName(111, u8"クッパドア");
    setName(112, u8"多砲身キラー砲台");
    setName(113, u8"プクプク（中）");
    setName(114, u8"プクプク(フォーメーション)");
    setName(115, u8"ＮＥＸＴＧＯＴＯブロック");
    setName(116, u8"中心君・振り子・レール対応版");
    setName(117, u8"中心君対応グルグル");
    setName(118, u8"中心君・回転・レール対応版");
    setName(119, u8"ジュゲム雲");
    setName(120, u8"トゲプク");
    setName(121, u8"霧範囲指定君");
    setName(122, u8"霧範囲指定君(ライト版)");
    setName(123, u8"間欠泉(砂)");
    setName(124, u8"常駐間欠泉(砂)");
    setName(125, u8"キラー");
    setName(126, u8"マグナムキラー");
    setName(127, u8"サーチキラー");
    setName(128, u8"マグナムサーチキラー");
    setName(129, u8"飛びプク");
    setName(130, u8"湧き出しジュゲム");
    setName(131, u8"飛びプク(湧き出し)");
    setName(132, u8"回転板");
    setName(133, u8"慣性線リフト");
    setName(134, u8"泡発生管理君");
    setName(135, u8"ドッスン");
    setName(136, u8"ドッスン（大）");
    setName(137, u8"カロン");
    setName(138, u8"カロン(大)");
    setName(139, u8"OBJ土管(上)");
    setName(140, u8"OBJ土管(下)");
    setName(141, u8"OBJ土管(左)");
    setName(142, u8"OBJ土管(右)");
    setName(143, u8"チビヨッシー(雲)");
    setName(144, u8"バルーン");
    setName(145, u8"椰子の木");
    setName(146, u8"回転土管");
    setName(147, u8"アクター線対応ハテナブロック");
    setName(148, u8"アクター線対応レンガブロック");
    setName(149, u8"アクター回転板追従コイン");
    setName(150, u8"モアイ");
    setName(151, u8"モアイ（下向き）");
    setName(152, u8"POWブロック");
    setName(153, u8"懐中電灯");
    setName(154, u8"アクターパタブロック");
    setName(155, u8"土管大砲");
    setName(156, u8"間欠泉(水)");
    setName(157, u8"回転砦横ブロック留め具");
    setName(158, u8"アクター通過コイン");
    setName(159, u8"伸縮土管(右)");
    setName(160, u8"伸縮土管(左)");
    setName(161, u8"伸縮土管(上)");
    setName(162, u8"伸縮土管(下)");
    setName(163, u8"常駐間欠泉(水)");
    setName(164, u8"ボム兵");
    setName(165, u8"親中心君コイン");
    setName(166, u8"親中心君通過コイン");
    setName(167, u8"青コイン");
    setName(168, u8"ＯＢＪコイン監視拍手君");
    setName(169, u8"ＯＢＪコイン常駐監視拍手君");
    setName(170, u8"パラボム兵");
    setName(171, u8"キラー砲台");
    setName(172, u8"伸縮キラー砲台");
    setName(173, u8"マグナムキラー砲台");
    setName(174, u8"マグナムキラー砲台（下向き）");
    setName(175, u8"メカクッパ");
    setName(176, u8"ナナメ砲台");
    setName(177, u8"回転砲台");
    setName(178, u8"回転砲台大");
    setName(179, u8"敵砲台弾");
    setName(180, u8"ガボン");
    setName(181, u8"ガボン（常駐）");
    setName(182, u8"半当たり上下移動リフト");
    setName(183, u8"ツララ");
    setName(184, u8"ツララ（大）");
    setName(185, u8"ツララ（固定）");
    setName(186, u8"半当たり左右移動リフト");
    setName(187, u8"連結ネズミ");
    setName(188, u8"トゲ鉄球湧き土管");
    setName(189, u8"アクターブロック雲");
    setName(190, u8"アクター回転制御ハテナブロック");
    setName(191, u8"アクター回転制御レンガブロック");
    setName(192, u8"湧き出しリフト");
    setName(193, u8"線リフト");
    setName(194, u8"ファイアスネーク");
    setName(195, u8"ルーレットブロック");
    setName(196, u8"グループＩＤ");
    setName(197, u8"風発生タグ");
    setName(198, u8"雪発生タグ");
    setName(199, u8"光るブロック");
    setName(200, u8"オブジェキノコ");
    setName(201, u8"火の粉発生君");
    setName(202, u8"プロペラブロック");
    setName(203, u8"氷ブロック(持てる)");
    setName(204, u8"チョロボン");
    setName(205, u8"アクター水面ハテナブロック");
    setName(206, u8"ブンブン（Ｗ１砦）");
    setName(207, u8"間欠泉(溶岩)");
    setName(208, u8"アクターブロックスイッチ");
    setName(209, u8"アクターブロックＰスイッチ");
    setName(210, u8"キノコリフト");
    setName(211, u8"回転半当たり床");
    setName(212, u8"オートスクロール");
    setName(213, u8"ぶらさがりツタ");
    setName(214, u8"回転制御君");
    setName(215, u8"ジャンプ台");
    setName(216, u8"ブンブンデモ管理タグ");
    setName(217, u8"親子オブジェ・子・砦用");
    setName(218, u8"テレサ");
    setName(219, u8"ビッグテレサ");
    setName(220, u8"回転拡縮テレサ（子）");
    setName(221, u8"回転拡縮テレサ（親）");
    setName(222, u8"スネークブロック");
    setName(223, u8"ブンブン（Ｗ２砦）");
    setName(224, u8"チビヨッシー(風船)");
    setName(225, u8"ブンブン（Ｗ６砦）");
    setName(226, u8"氷リフト(湧き出し)");
    setName(227, u8"氷リフト(湧き出し・浮く)");
    setName(228, u8"逆振り子リフト");
    setName(229, u8"キリフキー");
    setName(230, u8"ラリー");
    setName(231, u8"氷リフト(レール動作)");
    setName(232, u8"光るブロックリフト");
    setName(233, u8"アクターグループ線対応ハテナブロック");
    setName(234, u8"アクターグループ線対応レンガブロック");
    setName(235, u8"ファイアーバー");
    setName(236, u8"ファイアーバー2");
    setName(237, u8"書き換えブロック");
    setName(238, u8"ねじ回しで動く全当たり OBJ・親");
    setName(239, u8"ねじ回しで動く全当たり OBJ・子");
    setName(240, u8"丸太");
    setName(241, u8"スピン回転キノコ台");
    setName(242, u8"スピン回転キノコ台・子");
    setName(243, u8"チビヨッシー(泡)");
    setName(244, u8"コクッパの炎");
    setName(245, u8"コクッパデモ管理タグ");
    setName(246, u8"ブンブン（Ｗ４砦）");
    setName(247, u8"イガクリボー");
    setName(248, u8"回転枠・おばけ");
    setName(249, u8"ハナチャン");
    setName(250, u8"回転ブロック（全アタリ）");
    setName(251, u8"空中水");
    setName(252, u8"縄梯子");
    setName(253, u8"円ライト");
    setName(254, u8"深海用照明");
    setName(255, u8"マメクリボー");
    setName(256, u8"回転ブロック・キノコ");
    setName(257, u8"横伸縮キノコリフト");
    setName(258, u8"横伸縮キノコリフト（常駐）");
    setName(259, u8"ブラックパックン");
    setName(260, u8"砲門");
    setName(261, u8"パタメット");
    setName(262, u8"パタメット(大)");
    setName(263, u8"土管水流");
    setName(264, u8"間欠泉(水・ボス用)");
    setName(265, u8"床回転");
    setName(266, u8"回転ブロック・お化け");
    setName(267, u8"大甲羅");
    setName(268, u8"冷凍ブロック");
    setName(269, u8"歯車");
    setName(270, u8"ビリキュー");
    setName(271, u8"跳ね橋の腕");
    setName(272, u8"跳ね橋の支柱");
    setName(273, u8"跳ね橋の留め具");
    setName(274, u8"回転ブロック・カラー（空用）");
    setName(275, u8"溶岩振り子リフト");
    setName(276, u8"ライトクラゲ");
    setName(277, u8"アクター水面コイン");
    setName(278, u8"シーソーリフト");
    setName(279, u8"アクター画面追従コイン");
    setName(280, u8"スピン線リフト");
    setName(281, u8"アクター泡コイン");
    setName(282, u8"キングキラー");
    setName(283, u8"伸縮ブロック・親");
    setName(284, u8"伸縮ブロック・子(横)");
    setName(285, u8"伸縮ブロック・子(縦) ");
    setName(286, u8"バブル");
    setName(287, u8"水車リフト");
    setName(288, u8"フルーツの木");
    setName(289, u8"バーナー");
    setName(290, u8"バーナー(大)");
    setName(291, u8"同期バーナー管理OBJ");
    setName(292, u8"同期バーナー");
    setName(293, u8"回転バーナー");
    setName(294, u8"のぼり棒");
    setName(295, u8"ジャンプブロック");
    setName(296, u8"レミー");
    setName(297, u8"キノコリフト・親");
    setName(298, u8"アコヤ貝");
    setName(299, u8"リモコン上昇リフトのクリンチ");
    setName(300, u8"リモコン上昇定員リフト");
    setName(301, u8"大ハナチャン");
    setName(302, u8"ブンブン（Ｗ３砦）");
    setName(303, u8"コトン");
    setName(304, u8"グラグラ岩");
    setName(305, u8"ポルターガイスト");
    setName(306, u8"氷ブロック");
    setName(307, u8"移動金網");
    setName(308, u8"天秤リフト");
    setName(309, u8"天秤リフト戻り");
    setName(310, u8"燭台");
    setName(311, u8"全当たりポリゴン・砦用");
    setName(312, u8"線キノコブロック");
    setName(313, u8"ゲッソー");
    setName(314, u8"氷塊");
    setName(315, u8"天秤リフトステップ");
    setName(316, u8"回転ブロック・地下用");
    setName(317, u8"ブンブン（Ｗ５砦）");
    setName(318, u8"同期バブル");
    setName(319, u8"一定数乗ると動くリフト");
    setName(320, u8"クラッシャー");
    setName(321, u8"チョーチン");
    setName(322, u8"ゲッソー(ばら撒き)");
    setName(323, u8"樽ブロック");
    setName(324, u8"一定数乗ると動くお化けオブジェBG");
    setName(325, u8"回転制御君用通過コイン");
    setName(326, u8"アクター回転制御用コイン");
    setName(327, u8"ハンマー振り子");
    setName(328, u8"ねじ回し専用コイン");
    setName(329, u8"下向き大棍棒");
    setName(330, u8"一定数乗ると止まる溶岩リフト");
    setName(331, u8"上向き大棍棒");
    setName(332, u8"右向き大棍棒");
    setName(333, u8"左向き大棍棒");
    setName(334, u8"ペンタロー");
    setName(335, u8"ペンタロー(湧き土管)");
    setName(336, u8"イバラムシ");
    setName(337, u8"バクバク");
    setName(338, u8"木箱");
    setName(339, u8"木箱(湧き出し)");
    setName(340, u8"回転床同期コイン");
    setName(341, u8"ナット");
    setName(342, u8"右向きロング大棍棒");
    setName(343, u8"左向きロング大棍棒");
    setName(344, u8"特殊スクロールタグ");
    setName(345, u8"リモコンシーソーリフト");
    setName(346, u8"グループコトン");
    setName(347, u8"アクター石ブロック");
    setName(348, u8"お手本ブロック");
    setName(349, u8"リモコン横移動線リフト");
    setName(350, u8"回転砦横ブロック");
    setName(351, u8"サンボ");
    setName(352, u8"トゲメット");
    setName(353, u8"パラシュートコイン親");
    setName(354, u8"全当たり左右移動リフト");
    setName(355, u8"床回転(穴あき土管)");
    setName(356, u8"全当たり上下移動リフト");
    setName(357, u8"グループチョロボン");
    setName(358, u8"ねじ回しで動く足場");
    setName(359, u8"溶岩地面");
    setName(360, u8"ねじ回しで動くワイヤー");
    setName(361, u8"パラシュートコイン(湧き出し)");
    setName(362, u8"中心君対応土管ファイヤーパックン");
    setName(363, u8"宝箱");
    setName(364, u8"火山弾管理オブジェ");
    setName(365, u8"チビヨッシー(光る)");
    setName(366, u8"コインヘビ親");
    setName(367, u8"一定数乗ると動く半当たりリフト");
    setName(368, u8"モートン");
    setName(369, u8"南京玉すだれコイン・親");
    setName(370, u8"アクターキノコリフト追従コイン");
    setName(371, u8"レール動作の全あたりポリゴン・子");
    setName(372, u8"乗ると動くリフト");
    setName(373, u8"レール動作の全あたりポリゴン");
    setName(374, u8"溶岩振り子リフト中央");
    setName(375, u8"グルグル");
    setName(376, u8"親子オブジェ・子・城");
    setName(377, u8"全当たりポリゴン・開閉");
    setName(378, u8"トーピード基地");
    setName(379, u8"トーピード");
    setName(380, u8"子ヨッシー用ブロック");
    setName(381, u8"中心君対応ファイアーバー");
    setName(382, u8"ウナボン");
    setName(383, u8"ウェンディ");
    setName(384, u8"環境音タグ");
    setName(385, u8"ルドウィッグ");
    setName(386, u8"アクター冷凍コイン");
    setName(387, u8"サーチトーピード");
    setName(388, u8"観覧車リフト");
    setName(389, u8"ロイ");
    setName(390, u8"回転ブロック・木");
    setName(391, u8"回転ブロック・石");
    setName(392, u8"水中クッパJr");
    setName(393, u8"硬い氷ブロック");
    setName(394, u8"グループトーピード");
    setName(395, u8"星リフト");
    setName(396, u8"葉っぱリフト");
    setName(397, u8"アクター回転制御君用ハテナブロック");
    setName(398, u8"アクター回転制御君用レンガブロック");
    setName(399, u8"水中クッパJr");
    setName(400, u8"ライト付き半当たり回転リフト");
    setName(401, u8"シャッフルブロックマネージャ");
    setName(402, u8"緑リング");
    setName(403, u8"イギー");
    setName(404, u8"OBJ土管・上向きNEXTGOTO");
    setName(405, u8"親子オブジェ・子・組み合わせ");
    setName(406, u8"ボスK.K.");
    setName(407, u8"マリオ床地形アクター");
    setName(408, u8"ミニゲームキノピオ");
    setName(409, u8"ワンワン杭");
    setName(410, u8"モノレールブロック");
    setName(411, u8"カメック");
    setName(412, u8"カメックデモ管理タグ");
    setName(413, u8"シャドウ君");
    setName(414, u8"レミー飛行船");
    setName(415, u8"モートン飛行船");
    setName(416, u8"湧き出しサーチマグナムキラー");
    setName(417, u8"ラリー飛行船");
    setName(418, u8"ウェンディ飛行船");
    setName(419, u8"イギー飛行船");
    setName(420, u8"ロイ飛行船");
    setName(421, u8"ルドウィッグ飛行船");
    setName(422, u8"アクター巨大レンガブロック");
    setName(423, u8"ミニゲームマネージャ");
    setName(424, u8"ボス大砲（コクッパ飛行船乗り込み用）");
    setName(425, u8"木の枝伸縮リフト");
    setName(426, u8"風船吊るアクター");
    setName(427, u8"水に浮く氷ブロック");
    setName(428, u8"モノレールブロックのレール");
    setName(429, u8"親子オブジェ・子・互い違い");
    setName(430, u8"親子オブジェ・子・鉄");
    setName(431, u8"親子オブジェ・子・岩");
    setName(432, u8"ジュニアデモ管理タグ");
    setName(433, u8"ボクシングクッパJr.");
    setName(434, u8"回転ブロック・鉄");
    setName(435, u8"ボスK.K.デモ管理タグ");
    setName(436, u8"グループ線キノコブロック");
    setName(437, u8"クリボー");
    setName(438, u8"クリボー");
    setName(439, u8"お化け屋敷の回る部屋");
    setName(440, u8"わきだし火山弾");
    setName(441, u8"セイちゃん");
    setName(442, u8"中間ウナボン");
    setName(443, u8"ホネメット");
    setName(444, u8"水に浮く氷ブロック（大）");
    setName(445, u8"豆の木");
    setName(446, u8"雪玉");
    setName(447, u8"グループトゲメット");
    setName(448, u8"水中クッパJr.用トーピード生成タグ");
    setName(449, u8"宝箱のカギ");
    setName(450, u8"カメックツララ配置");
    setName(451, u8"クエストアクター配置タグ");
    setName(452, u8"スロットチビヨッシー");
    setName(453, u8"マジックハンドパー");
    setName(454, u8"マジックハンドグー");
    setName(455, u8"範囲指定コイン監視拍手君");
    setName(456, u8"カメックワープ位置");
    setName(457, u8"波打つ床地形アクター");
    setName(458, u8"コインバトル用土管・下向きNEXTGOTO");
    setName(459, u8"W8道中クッパJr");
    setName(460, u8"マジックハンドタグパー");
    setName(461, u8"マジックハンドタググー");
    setName(462, u8"クッパ");
    setName(463, u8"ボスクッパスイッチボタン");
    setName(464, u8"クッパ用足場");
    setName(465, u8"カメックブロック");
    setName(466, u8"城クッパデモ管理タグ");
    setName(467, u8"クッパシャッター");
    setName(468, u8"クッパ炎（湧き出し）");
    setName(469, u8"ピーチ");
    setName(470, u8"紫リング");
    setName(471, u8"中クリボー");
    setName(472, u8"大クリボー");
    setName(473, u8"最終クッパ");
    setName(474, u8"コインまき砲台");
    setName(475, u8"アクター巨大ハテナブロック");
    setName(476, u8"でかノコノコ");
    setName(477, u8"最終クッパJr");
    setName(478, u8"ボクシングクッパJr.専用床");
    setName(479, u8"親子オブジェ・子・警告");
    setName(480, u8"回転制御用コレクションコイン");
    setName(481, u8"ニセムサ");
    setName(482, u8"メカプクプク");
    setName(483, u8"同期ファイアーバー");
    setName(484, u8"条件フラグ付き回転制御君");
    setName(485, u8"親子オブジェ・子・互い違い歯車");
    setName(486, u8"フレーム設定タグ");
    setName(487, u8"クッパ専用エリアＯＢＪ");
    setName(488, u8"土管ウナボン");
    setName(489, u8"飛行船の底");
    setName(490, u8"飛行船の底の枠");
    setName(491, u8"W8道中クッパJr.用半当たり上下移動リフト");
    setName(492, u8"W8道中クッパJr.用半当たり左右移動リフト");
    setName(493, u8"全当たりポリゴン・飛行船");
    setName(494, u8"水中クッパJr.退避位置");
    setName(495, u8"吸い込み水タグ");
    setName(496, u8"アクター重力付コイン");
    setName(497, u8"最終クッパデモ管理タグ");
    setName(498, u8"アクターコイン噴水湧き出しタグ");
    setName(499, u8"親子オブジェ・子・野原用・半当たり");
    setName(500, u8"クッパ電線");
    setName(501, u8"クッパ電線タグ");
    setName(502, u8"クッパ電線単体");
    setName(503, u8"絵画ステージ用ゴールポール");
    setName(504, u8"ゴロゴロ");
    setName(505, u8"ゴロゴロ（巨大）");
    setName(506, u8"チャレンジモード専用ブロック");
    setName(507, u8"流れ星スター");
    setName(508, u8"乗ると動くリフト空用");
    setName(509, u8"OBJ土管・右向きNEXTGOTO");
    setName(510, u8"OBJ土管・左向きNEXTGOTO");
    setName(511, u8"OBJ土管・下向きNEXTGOTO");
    setName(512, u8"回転ブロック・お化け屋敷の沈没船");
    setName(513, u8"土管ジョイント描画");
    setName(514, u8"土管ジョイントマメ描画");
    setName(515, u8"親子オブジェ・子・溶岩城");
    setName(516, u8"マメマリオ用OBJ土管(右)");
    setName(517, u8"マメマリオ用OBJ土管(左)");
    setName(518, u8"マメマリオ用OBJ土管(上)");
    setName(519, u8"マメマリオ用OBJ土管(下)");
    setName(520, u8"ボスクッパ斧付スイッチボタン");
    setName(521, u8"ゴールキノコハウス描画");
    setName(522, u8"浮き樽");
    setName(523, u8"敵コース用アクターパタブロック");
    setName(524, u8"親子オブジェ・子・砦岩");
    setName(525, u8"画面追従ハテナブロック");
    setName(526, u8"画面追従レンガブロック");
    setName(527, u8"ピーチデモ管理タグ");
    setName(528, u8"全水中エフェクトフィルター");
    setName(529, u8"クロスケー");
    setName(530, u8"ねじ回しで動く全当たり OBJ・子・ピラミッド");
    setName(531, u8"泡");
    setName(532, u8"ロイ用湧き出しリフト");
    setName(533, u8"ウェンディのツララ");
    setName(534, u8"同期半当たり左右移動リフト");
    setName(535, u8"同期半当たり上下移動リフト");
    setName(536, u8"マンホールプー");
    setName(537, u8"スパナ");
    setName(538, u8"クッキー");
    setName(539, u8"ガッタン");
    setName(540, u8"フライングキノコ");
    setName(541, u8"フライングキノコ(湧き出し)");
    setName(542, u8"キノコ足場・左右移動");
    setName(543, u8"クエスト用キノピオ");
    setName(544, u8"カラーキノコリフト");
    setName(545, u8"湧き出しバクバク");
    setName(546, u8"追従草花");
    setName(547, u8"クエストの景品アイテム");
    setName(548, u8"光で現れるブロック");
    setName(549, u8"親子オブジェ・子・砂漠の遺跡");
    setName(550, u8"でか土管パックンフラワー");
    setName(551, u8"マジックハンド・水中クッパJr.デモ用");
    setName(552, u8"ブラックパックンOBJ");
    setName(553, u8"進行方向切換リフト");
    setName(554, u8"ムササビプレイヤー参照タグ");
    setName(555, u8"玉乗りリフト");
    setName(556, u8"チビヨッシー（泡）（スタッフロール）");
    setName(557, u8"スタッフロールマネージャ");
    setName(558, u8"W8道中クッパJr.管理タグ");
    setName(559, u8"シャドウ君退避タグ");
    setName(560, u8"ウェンディの床");
    setName(561, u8"シャドウ君の家の読むタグ");
    setName(562, u8"全当たりポリゴン・高原用");
    setName(563, u8"親子オブジェ・子・高原用");
    setName(564, u8"草花種類指定タグ");
    setName(565, u8"ウーチャン");
    setName(566, u8"クエスト専用ブロック");
    setName(567, u8"湧き出しケロンパ");
    setName(568, u8"ウナボン(復活)");
    setName(569, u8"クエスト用デモロケーションタグ");
    setName(570, u8"ショートプレイ結果デモタグ");
    setName(571, u8"ショートプレイ結果画面のピーチ姫");
    setName(572, u8"ＤＶ草花発生");
    setName(573, u8"同期線リフト");
    setName(574, u8"コインバトル用土管・上向きNEXTGOTO");
    setName(575, u8"OBJ土管(左・グループ)");
    setName(576, u8"OBJ土管(右・グループ)");
    setName(577, u8"OBJ土管(上・グループ)");
    setName(578, u8"OBJ土管(下・グループ)");
    setName(579, u8"ロックガボン");
    setName(580, u8"ロックガボン（常駐）");
    setName(581, u8"サーチキラー砲台");
    setName(582, u8"サーチマグナムキラー砲台");
    setName(583, u8"サーチマグナムキラー砲台（下向き）");
    setName(584, u8"鉄箱");
    setName(585, u8"鉄箱(湧き出し)");
    setName(586, u8"飛びメカプク(湧き出し)");
    setName(587, u8"飛びメカプク");
    setName(588, u8"サーチプクプク");
    setName(589, u8"サーチプクプク（中）");
    setName(590, u8"にげプクプク");
    setName(591, u8"にげプクプク（中）");
    setName(592, u8"サーチプクプク(湧き出し)");
    setName(593, u8"K.K.");
    setName(594, u8"K.K.の雷");
    setName(595, u8"カキボー");
    setName(596, u8"サーチトーピード基地");
    setName(597, u8"にげプクプク(湧き出し)");
    setName(598, u8"お題モード足場");
    setName(599, u8"ゴールリング");
    setName(600, u8"DRC画面にしか見えないブロック");
    setName(601, u8"敵コースデモ用シャドウ君");
    setName(602, u8"つかまり鎖");
    setName(603, u8"毒霧");
    setName(604, u8"戦闘後デモボクシングクッパJr.");
    setName(605, u8"戦闘後デモボクシングクッパJr.のクラウン");
    setName(606, u8"こでかメット");
    setName(607, u8"グループコレクションコイン線対応");
    setName(608, u8"タッチ無効アクター");
    setName(609, u8"イギー部屋");
    setName(610, u8"ショートプレイ結果デモタグ");
    setName(611, u8"クエスト用キノピオ");
    setName(612, u8"Ｐムササビブロック");
    setName(613, u8"コインバトル用土管・左向きNEXTGOTO");
    setName(614, u8"コインバトル用土管・右向きNEXTGOTO");
    setName(615, u8"グループプクプク");
    setName(616, u8"グループプクプク管理タグ");
    setName(617, u8"シャボン保護地帯タグ");
    setName(618, u8"アクター壊れないブロック");
    setName(619, u8"アクター木ブロック");
    setName(620, u8"でかフグマンネン");
    setName(621, u8"でかフグマンネン(湧き出し)");
    setName(622, u8"エディットコインアクター設置範囲タグ");
    setName(623, u8"境界速度調整君");
    setName(624, u8"グループＩＤトゲメット用");
    setName(625, u8"ねじ回しで動く全当たり OBJ・子・ピラミッド・常駐");
    setName(626, u8"K.K.(常駐)");
    setName(627, u8"W8道中クッパJr.用半アタリ移動リフト（親子オブジェ対応）");
    setName(628, u8"マジックハンドタググー・速い");
    setName(629, u8"湧き出しジュゲム(マルチプレイ用)");
    setName(630, u8"ゴールポール(RDash)");
    setName(631, u8"絵画ステージ用ゴールポール(RDash)");
    setName(632, u8"シーソーリフト(RDash)");
    setName(633, u8"リモコン上昇定員リフト(RDash)");
    setName(634, u8"RDashルイージブロック");
    setName(635, u8"城のドア(RDash用)");
    setName(636, u8"砦のドア(RDash用)");
    setName(637, u8"クッパドア(RDash用)");
    setName(638, u8"ウナボン(RDash)");
    setName(639, u8"土管NextGotoタイマー加算タグ");
    setName(640, u8"RDash用ケロンパ");
    setName(641, u8"ワンワン杭(RDash)");
    setName(642, u8"親子オブジェ・親(R-Dash専用版)");
    setName(643, u8"バブル(RDash)");
    setName(644, u8"同期バブル(RDash)");
    setName(645, u8"回転ブロック・木(RDash)");
    setName(646, u8"マグナムキラー砲台(RDash)");
    setName(647, u8"マグナムキラー砲台（下向き）(RDash)");
    setName(648, u8"サーチマグナムキラー砲台(RDash)");
    setName(649, u8"サーチマグナムキラー砲台（下向き）(RDash)");
    setName(650, u8"コレクション親制御(RDash)");
    setName(651, u8"ガボン(RDash)");
    setName(652, u8"パタメット");
    setName(653, u8"キングキラー(RDash)");
    setName(654, u8"タイトルデモ用シャドウ君");
    setName(655, u8"スネークブロック(RDash用)");
    setName(656, u8"ズーム君(RDash)");
    setName(657, u8"ピーチデモ用シャドウ君");
    setName(658, u8"線リフトRDash");
    setName(659, u8"ゴロゴロ（巨大RDash）");
    setName(660, u8"フラグスイッチ条件フラグＲＤＡＳＨ用");
    setName(661, u8"K.K.(リフト修正版)");
    setName(662, u8"青リング");
    setName(663, u8"アクターコインＲＤＡＳＨ用");
    setName(664, u8"ウナボン(復活RDash)");
    setName(665, u8"コレクション親制御(RDash生成範囲拡張版)");
    setName(666, u8"マジックハンドグー(RDash)");
    setName(667, u8"土管大砲(RDash)");
    setName(668, u8"飛行船の底(RDash)");
    setName(669, u8"親子オブジェ・子・砦岩(RDash用)");
    setName(670, u8"ミニゲームマネージャ(RDash)");
    setName(671, u8"トゲ鉄球通り穴(RDash用2砦)");
    setName(672, u8"レールエフェクト発生ブロック");
    setName(673, u8"書き換えブロック(RDash用)");
    setName(674, u8"溶岩地面(RDash)");
    setName(675, u8"歯車(RDash)");
    setName(676, u8"溶岩振り子リフト(RDash)");
    setName(677, u8"全水中エフェクトフィルター(RDash)");
    setName(678, u8"アクター透明ブロックRDash");
    setName(679, u8"回転土管(RDash)");
    setName(680, u8"RDash5-5専用モアイ");
    setName(681, u8"看板矢印(RDash)");
    setName(682, u8"水面パックン(RDash)");
    setName(683, u8"アクターハテナブロック(RDash)");
    setName(684, u8"ハイパーマックス上君（左）");
    setName(685, u8"ハイパーマックス上君（右）");
    setName(686, u8"スイッチＰボタン(RDash)");
    setName(687, u8"パラボム兵(RDash)");
    setName(688, u8"鉄箱(RDash)");
    setName(689, u8"スタッフロールマネージャ");
    setName(690, u8"ルイージ看板（１−１）");
    setName(691, u8"ルイージ看板（９−９）");
    setName(692, u8"アクターレンガブロック(RDash)");
    setName(693, u8"中心君対応グルグル(RDash)");
    setName(694, u8"専用お化け屋敷の全当たりポリゴン");
    setName(695, u8"ウニラ(RDash用)");
    setName(696, u8"回転ブロック・お化け(RD4-化け専用)");
    setName(697, u8"鉄箱(RDash-生成範囲狭い版)");
    setName(698, u8"地面パックンフラワー(RDash)");
    setName(699, u8"慣性線リフト親(RDash)");
    setName(700, u8"慣性線リフト子(RDash)");
    setName(701, u8"アクターレンガブロック（レール縦方向）");
    setName(702, u8"ハナチャン");
    setName(703, u8"回転拡縮テレサRDash（親）");
    setName(704, u8"アクター回転制御レンガブロック(RDash)");
    setName(705, u8"RD3-3専用常駐間欠泉(水)");
    setName(706, u8"回転制御レンガブロック(R99)");
    setName(707, u8"アクター回転制御ハテナブロック(R99)");
    setName(708, u8"プレイヤー画面横挟み要求タグ");
    setName(709, u8"回転ブロック・鉄(RDASH用)");
    setName(710, u8"スイッチＰボタン(壁キック無効版)");
    setName(711, u8"回転ブロック・鉄(RDASH用その2)");
    setName(712, u8"地面パックンフラワー(R33)");
    setName(713, u8"ウニラ・RDASH・BGチェック狭い版");
    setName(714, u8"逆振り子リフト(RDash当たり消えない版)");
    setName(715, u8"フラグスイッチ条件フラグＲ６３用");
    setName(716, u8"キリフキー(RDash)");
    setName(717, u8"スネークブロック(R76用)");
    setName(718, u8"シャドウ君の家の読むタグ");
    setName(719, u8"RDash2-4専用モアイ");
    setName(720, u8"RDash2-4専用モアイ（下向き）");
    setName(721, u8"コレクション親制御(R６城)");
    setName(722, u8"看板矢印(生成範囲狭い版)");
    setName(723, u8"グループプクプク（中）");

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

void ActorCreateMgr::setMaxID(u16 max_num)
{
    RIO_ASSERT(max_num >= mMaxID); // Can only go up, for now
    mMaxID = max_num;
}

u16 ActorCreateMgr::getMaxID() const
{
    return mMaxID;
}

void ActorCreateMgr::setName(u16 map_actor_id, const std::u8string& name)
{
    RIO_ASSERT(map_actor_id < mMaxID);
    mMapActorNameMap[map_actor_id] = name;
}

const std::u8string& ActorCreateMgr::getName(u16 map_actor_id) const
{
    const auto& itr = mMapActorNameMap.find(map_actor_id);
    if (itr != mMapActorNameMap.end())
        return itr->second;

    static const std::u8string empty = u8"";
    return empty;
}

void ActorCreateMgr::setActorFactory(u16 map_actor_id, ActorFactory factory, const MapActorData* default_data)
{
    RIO_ASSERT(map_actor_id < mMaxID);
    mActorFactoryMap[map_actor_id] = std::pair { factory, default_data };
}

const std::pair<ActorFactory, const MapActorData*>* ActorCreateMgr::getActorFactory(u16 map_actor_id) const
{
    const auto& itr = mActorFactoryMap.find(map_actor_id);
    if (itr != mActorFactoryMap.end())
        return &itr->second;

    return nullptr;
}

std::unique_ptr<MapActorItem> ActorCreateMgr::create(const MapActorData& map_actor_data, u32 index) const
{
    const auto& itr = mActorFactoryMap.find(map_actor_data.id);
    if (itr != mActorFactoryMap.end())
        return (*itr->second.first)(map_actor_data, index);

    return std::make_unique<MapActorItem>(map_actor_data, index);
}
