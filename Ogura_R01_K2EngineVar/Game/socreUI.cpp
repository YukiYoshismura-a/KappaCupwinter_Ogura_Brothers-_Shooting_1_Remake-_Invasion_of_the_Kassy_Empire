#include "stdafx.h"
#include "socreUI.h"

socreUI::socreUI()
{
	// 基準となる右下の座標（ここが右端のポジションになるイメージ）
	// フォントの基本サイズや文字幅に合わせて微調整してな！
	fontRender.SetPosition({ 800.0f, -480.0f, 0.0f });

	// 文字の大きさ
	fontRender.SetScale(1.2f);

	// 文字の色
	fontRender.SetColor(1.0f, 0.0f, 0.0f, 1.0f);
}

socreUI::~socreUI()
{
}

void socreUI::Update()
{
	// 表示する文字列を作成
	wchar_t text[256];
	swprintf_s(text, L"%d", m_score); // 得点の数字だけ（必要なら L"SCORE: %d" でもOK）

	// FontRenderにテキストをセット
	fontRender.SetText(text);

	// ★ 桁数（文字数）に合わせてX座標を左にずらし、右端を固定する！
	// 1文字あたりの幅の目安（スケール1.2なら大体20〜25ピクセルくらい）
	int length = lstrlenW(text);
	float charWidth = 22.0f * 1.2f; // 「文字の基本幅 × スケール」

	// 基準のX座標（800.0f）から、文字数分だけ左（マイナス方向）にずらす
	float baseX = 800.0f;
	float rightAlignedX = baseX - (length * charWidth);

	// 位置を再設定
	Vector3 pos = fontRender.GetPosition();
	pos.x = rightAlignedX;
	fontRender.SetPosition(pos);
}

void socreUI::Render(RenderContext& rc)
{
	fontRender.Draw(rc);
}