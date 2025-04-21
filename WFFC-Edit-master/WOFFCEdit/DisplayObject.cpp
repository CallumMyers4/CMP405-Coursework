#include "DisplayObject.h"

DisplayObject::DisplayObject()
{
	m_model = NULL;
	m_texture_diffuse = NULL;
	m_orientation.x = 0.0f;
	m_orientation.y = 0.0f;
	m_orientation.z = 0.0f;
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;
	m_scale.x = 0.0f;
	m_scale.y = 0.0f;
	m_scale.z = 0.0f;
	m_render = true;
	m_wireframe = false;

	m_light_type =0;
	m_light_diffuse_r = 0.0f;	m_light_diffuse_g = 0.0f;	m_light_diffuse_b = 0.0f;
	m_light_specular_r = 0.0f;	m_light_specular_g = 0.0f;	m_light_specular_b = 0.0f;
	m_light_spot_cutoff = 0.0f;
	m_light_constant = 0.0f;
	m_light_linear = 0.0f;
	m_light_quadratic = 0.0f;
}


DisplayObject::~DisplayObject()
{
//	delete m_texture_diffuse;
}

//change the colour of an object
void DisplayObject::ChangeColour(bool enable)
{
	//https://github.com/microsoft/DirectXTK/wiki/Rendering-a-model

	//add fog to the model
	m_model->UpdateEffects([enable](DirectX::IEffect* effect)
	{
		auto highlightFog = dynamic_cast<DirectX::IEffectFog*>(effect);		//make a fog effect

		//as long as fog was made right
		if (highlightFog != nullptr)
		{
			highlightFog->SetFogEnabled(enable);	//either enable or disable the effect based on the parameter input
			highlightFog->SetFogColor(DirectX::Colors::WhiteSmoke);		//make model white
		}
	});
}