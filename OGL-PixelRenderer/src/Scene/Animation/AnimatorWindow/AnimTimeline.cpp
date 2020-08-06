#include "AnimTimeline.h"

#include <GLFW/glfw3.h>

void AnimTimeline::Update()
{
	float time = glfwGetTime();
	loopCount = int(time/_animationDuration);
	_currentTime = time-(loopCount*_animationDuration);

	if (!_show)
		return;

	ImGuiStyle& style = ImGui::GetStyle();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, style.WindowBorderSize });
	if (!Begin())
		End();

	else {
		ImVec2 window_size = ImGui::GetWindowSize();
		ImVec2 region_size = ImGui::GetContentRegionAvail();

		printf("regionsize: (%f, %f)\n", region_size.x, region_size.y);
		//Header
		static float headerEndPos = 0;
		ImGui::BeginChild("###controller", { region_size.x * 0.3f , region_size.y }, true);
		{
			ImGui::Text("Controller Area");
			ImGui::ArrowButton("Oie", ImGuiDir_Right);
			ImGui::SameLine();
			ImGui::Button("| |");
		}
		ImGui::EndChild();

		ImGui::SameLine();

		ImGui::BeginChild("###animator", { region_size.x * 0.7f , region_size.y });
		{
			ImGui::BeginGroup(); {

				ImGui::BeginGroup(); 
				{
					ImGui::Text("FPS");
					ImGui::SameLine();
					ImGui::SetNextItemWidth(50);
					ImGui::SliderInt("###fps", &_frameSampling, 0, 60);
					ImGui::SameLine();

					ImGui::Text("Initial Frame");
					ImGui::SameLine();
					ImGui::SetNextItemWidth(50);
					ImGui::SliderInt("###start", &_initialFrame, 0, _finalFrame);
					ImGui::SameLine();

					ImGui::Text("Last Frame");
					ImGui::SameLine();
					ImGui::SetNextItemWidth(50);
					ImGui::SliderInt("###end", &_finalFrame, _initialFrame, _maxFrames);
					ImGui::EndGroup();
				}

				ImGui::BeginGroup();
				{
					ImGui::Text("Current Frame");
					ImGui::SameLine();
					ImGui::Text(std::to_string(_currentFrame).c_str());
					ImGui::SameLine(0, 25); 
					ImGui::Text("Current Time");
					ImGui::SameLine();
					ImGui::Text(std::to_string(_currentTime).c_str());
					ImGui::EndGroup();
				}

				ImGui::Separator();
				ImGui::EndGroup();
				headerEndPos = ImGui::GetItemRectMax().y + 6;
			}

			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			ImGui::PushID("##HorizontalScrolling");
			float child_height = ImGui::GetTextLineHeight() + style.ScrollbarSize + style.WindowPadding.y * 2.0f;
			ImGuiWindowFlags child_flags = ImGuiWindowFlags_HorizontalScrollbar;
			ImGuiID child_id = ImGui::GetID((void*)(intptr_t)0);
			bool child_is_visible = ImGui::BeginChild(child_id, ImVec2(-1, child_height), true, child_flags);
			if (child_is_visible) // Avoid calling SetScrollHereY when running with culled items
			{
				for (int item = 0; item < 100; item+=10)
				{
					ImGui::Text("%d", item);
					ImVec2 size = ImGui::GetItemRectSize();
					ImGui::SameLine(0, size.x*10);
				}
			}
			ImGui::EndChild();
			ImGui::PopID();


			ImVec2 size = ImGui::GetItemRectSize();

			ImVec2 window_pos = ImGui::GetWindowPos();
			ImVec2 window_center = ImVec2(window_pos.x + window_size.x * 0.5f, window_pos.y + window_size.y * 0.5f);


			float pct = _currentTime / _animationDuration;
			float offsetX = pct*(region_size.x*0.7f-10.f);

			ImVec2 top{ window_pos.x + offsetX, headerEndPos };
			ImVec2 bottom{ window_pos.x + offsetX, window_pos.y + window_size.y + size.y };

			draw_list->AddLine(top, bottom, IM_COL32(255, 0, 0, 150), 1.5f);
		}
		ImGui::EndChild();
		ImGui::PopStyleVar();

		//Timeline



		End();
	}
}
