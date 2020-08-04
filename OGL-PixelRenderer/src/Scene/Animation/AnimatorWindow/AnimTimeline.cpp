#include "AnimTimeline.h"

void AnimTimeline::Update()
{
	if (!_show)
		return;

	ImGuiStyle& style = ImGui::GetStyle();
	if (!Begin())
		End();

	else {
		//Header
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
		}
		ImGui::EndGroup();

		ImGui::BeginGroup();
		{
			ImGui::Text("Current Frame");
			ImGui::SameLine();
			ImGui::Text(std::to_string(_currentFrame).c_str());
			ImGui::SameLine(0, 25); 
			ImGui::Text("Current Time");
			ImGui::SameLine();
			ImGui::Text(std::to_string(_currentTime).c_str());
		}
		ImGui::EndGroup();

		//Timeline
		ImGui::Separator();

		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		ImGui::PushID("##HorizontalScrolling");
		float child_height = ImGui::GetTextLineHeight() + style.ScrollbarSize + style.WindowPadding.y * 2.0f;
		ImGuiWindowFlags child_flags = ImGuiWindowFlags_HorizontalScrollbar;
		ImGuiID child_id = ImGui::GetID((void*)(intptr_t)0);
		bool child_is_visible = ImGui::BeginChild(child_id, ImVec2(-1, child_height), true, child_flags);
		if (child_is_visible) // Avoid calling SetScrollHereY when running with culled items
		{
			for (int item = 0; item < 100; item++)
			{
				ImGui::Text("Item %d", item);
				ImGui::SameLine();
			}
		}
		ImGui::EndChild();
		ImGui::PopID();

		ImVec2 window_pos = ImGui::GetWindowPos();
		ImVec2 window_size = ImGui::GetWindowSize();
		ImVec2 window_center = ImVec2(window_pos.x + window_size.x * 0.5f, window_pos.y + window_size.y * 0.5f);
		ImVec2 top{ window_center.x + _finalFrame, window_center.y + window_size.y/2 };
		ImVec2 bottom{ window_center.x + _finalFrame, window_center.y - window_size.y/2};
		draw_list->AddLine(top, bottom, IM_COL32(255, 0, 0, 150), 1.5f);

		End();
	}
}
