bool 自动旋转 = false;
bool 循环缩放 = false;
float 六芒星X = 300.0f;
float 六芒星Y = 200.0f;
float 六芒星大小 = 50.0f;
float 缩放幅度 = 20.0f;
float 旋转速度 = 0.8f;
float 缩放速度 = 1.5f;
int 渐变细腻效果 = 15;
float 渐变起始色[4] = {1.0f, 0.588f, 0.784f, 1.0f};
float 渐变结束色[4] = {0.392f, 1.0f, 1.0f, 1.0f};
float 起始色覆盖比例 = 0.2f;


void byqingyunHZLBX(float x, float y, float size, float rotation, ImDrawList* draw, ImU32 color) {
const int numPoints = 6;
ImVec2 center(x, y);
ImVec2 points[numPoints];
for (int i = 0; i < numPoints; i++) {
float angle = rotation + 2 * IM_PI * i / numPoints;
points[i] = ImVec2(center.x + size * cos(angle), center.y + size * sin(angle));
}
ImVec2 triangle1[3] = { points[0], points[2], points[4] };
ImVec2 triangle2[3] = { points[1], points[3], points[5] };
draw->AddConvexPolyFilled(triangle1, 3, color);
draw->AddConvexPolyFilled(triangle2, 3, color);
}


if (设置.六芒星) {
ImVec2 starCenter(设置.六芒星X, 设置.六芒星Y);
int jianbianxilixiaoguo = 设置.渐变细腻效果;
float daxiao = 设置.六芒星大小;
float suofangfudu = 设置.缩放幅度;
float xuazhuangsudu = 设置.旋转速度;
float suofangsudu = 设置.缩放速度;
float qishise = 设置.起始色覆盖比例;

ImU32 gradientStartColor = IM_COL32(
(int)(设置.渐变起始色[0] * 255),
(int)(设置.渐变起始色[1] * 255),
(int)(设置.渐变起始色[2] * 255),
255
);
ImU32 gradientEndColor = IM_COL32(
(int)(设置.渐变结束色[0] * 255),
(int)(设置.渐变结束色[1] * 255),
(int)(设置.渐变结束色[2] * 255),
255
);

float time = ImGui::GetTime();
float currentSize = daxiao;
float currentRotation = 0.0f;

if (设置.循环缩放) {
currentSize = daxiao + suofangfudu * sin(time * suofangsudu);
}
if (设置.自动旋转) {
currentRotation = time * xuazhuangsudu;
}

int startR = (gradientStartColor >> 0) & 0xFF;
int startG = (gradientStartColor >> 8) & 0xFF;
int startB = (gradientStartColor >> 16) & 0xFF;
int endR = (gradientEndColor >> 0) & 0xFF;
int endG = (gradientEndColor >> 8) & 0xFF;
int endB = (gradientEndColor >> 16) & 0xFF;

auto calculateLayerColor = [&](int layerIndex){
float layerRatio = (float)layerIndex / (jianbianxilixiaoguo - 1);
float t = (layerRatio - qishise) / (1.0f - qishise);
t = ImClamp(t, 0.0f, 1.0f);
int mixR = startR + (endR - startR) * t;
int mixG = startG + (endG - startG) * t;
int mixB = startB + (endB - startB) * t;
return IM_COL32(mixR, mixG, mixB, 255);
};

for (int layer = 0; layer < jianbianxilixiaoguo; ++layer) {
float layerSize = currentSize * (1.0f - (float)layer / jianbianxilixiaoguo);
ImU32 currentColor = calculateLayerColor(layer);
byqingyunHZLBX(starCenter.x, starCenter.y, layerSize, currentRotation, draw, currentColor);
}
}



if (设置.六芒星){
if (ImGui::CollapsingHeader("六芒星动效设置")) {
ImGui::Text("中心点位置调节");
ImGui::SliderFloat("X坐标", &设置.六芒星X, 50.0f, ImGui::GetIO().DisplaySize.x - 50.0f);
ImGui::SliderFloat("Y坐标", &设置.六芒星Y, 50.0f, ImGui::GetIO().DisplaySize.y - 50.0f);

ImGui::Separator();

ImGui::Text("大小调节");
ImGui::SliderFloat("基础大小", &设置.六芒星大小, 10.0f, 150.0f);
ImGui::Checkbox("启用循环缩放", &设置.循环缩放);
if (设置.循环缩放) {
ImGui::Indent();
ImGui::SliderFloat("缩放幅度", &设置.缩放幅度, 5.0f, 80.0f);
ImGui::SliderFloat("缩放速度", &设置.缩放速度, 0.2f, 5.0f);
ImGui::Unindent();
}
ImGui::Separator();

ImGui::Text("旋转调节");
ImGui::Checkbox("启用自动旋转", &设置.自动旋转);
if (设置.自动旋转) {
ImGui::Indent();
ImGui::SliderFloat("旋转速度", &设置.旋转速度, -6.0f, 6.0f);
ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "提示：负值为逆时针旋转");
ImGui::Unindent();
}
ImGui::Separator();

ImGui::Text("渐变调节");
ImGui::SliderInt("渐变细腻效果", &设置.渐变细腻效果, 3, 50);
ImGui::ColorEdit4("渐变起始色", 设置.渐变起始色, ImGuiColorEditFlags_NoAlpha);
ImGui::ColorEdit4("渐变结束色", 设置.渐变结束色, ImGuiColorEditFlags_NoAlpha);
ImGui::SliderFloat("起始色覆盖比例", &设置.起始色覆盖比例, 0.0f, 0.8f);
}
}
