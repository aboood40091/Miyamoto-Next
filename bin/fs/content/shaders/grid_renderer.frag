#version 330 core

uniform vec4  uColor;
uniform float uPixelsPerUnit;
uniform int   uMode;

in vec2 vWorldPos;

layout (location = 0) out vec4 FragColor;

const float cTile = 16.0;

float lineCoverage(float coord, float period, float width_px)
{
    float scaled = coord / period;
    float dist_px = abs(fract(scaled - 0.5) - 0.5) * period * uPixelsPerUnit;

    return 1.0 - smoothstep(width_px * 0.5 - 0.5, width_px * 0.5 + 0.5, dist_px);
}

float dashMask(float along_px, float width_px, float on, float off)
{
    float period = (on + off) * width_px;
    float phase = fract(along_px / period) * period;

    return 1.0 - smoothstep(on * width_px - 0.5, on * width_px + 0.5, phase);
}

float tierFade(float tile_px, float cutoff_px)
{
    return smoothstep(cutoff_px * 0.5, cutoff_px, tile_px);
}

vec4 drawLines(float tile_px)
{
    vec2 along_px = vWorldPos * uPixelsPerUnit;

    float alpha = 0.0;

    // Minor: every tile, dotted, 1 px
    {
        float fade = tierFade(tile_px, 12.0);
        if (fade > 0.0)
        {
            float x = lineCoverage(vWorldPos.x, cTile, 1.0) * dashMask(along_px.y, 1.0, 1.0, 2.0);
            float y = lineCoverage(vWorldPos.y, cTile, 1.0) * dashMask(along_px.x, 1.0, 1.0, 2.0);
            alpha = max(alpha, max(x, y) * fade);
        }
    }

    // Medium: every 4 tiles, dashed, 1 px
    {
        float fade = tierFade(tile_px, 6.0);
        if (fade > 0.0)
        {
            float x = lineCoverage(vWorldPos.x, cTile * 4.0, 1.0) * dashMask(along_px.y, 1.0, 4.0, 2.0);
            float y = lineCoverage(vWorldPos.y, cTile * 4.0, 1.0) * dashMask(along_px.x, 1.0, 4.0, 2.0);
            alpha = max(alpha, max(x, y) * fade);
        }
    }

    // Major: every 8 tiles, dashed, 2 px
    {
        float x = lineCoverage(vWorldPos.x, cTile * 8.0, 2.0) * dashMask(along_px.y, 2.0, 4.0, 2.0);
        float y = lineCoverage(vWorldPos.y, cTile * 8.0, 2.0) * dashMask(along_px.x, 2.0, 4.0, 2.0);
        alpha = max(alpha, max(x, y));
    }

    return vec4(uColor.rgb, uColor.a * alpha);
}

vec4 drawChecker(float tile_px)
{
    float size = (tile_px >= 12.0) ? cTile : cTile * 8.0;

    vec2 cell = floor(vWorldPos / size);

    float parity = mod(cell.x + cell.y, 2.0);
    float block  = mod(floor(cell.x * 0.25) + floor(cell.y * 0.25), 2.0);

    float alpha =
        (parity < 0.5)
            ? 0.1
            : ((block < 0.5) ? 0.0 : 0.2);

    return vec4(uColor.rgb, uColor.a * alpha);
}

void main()
{
    float tile_px = cTile * uPixelsPerUnit;

    vec4 color =
        (uMode == 0)
            ? drawLines(tile_px)
            : drawChecker(tile_px);

    if (color.a <= 0.0)
        discard;

    FragColor = color;
}
