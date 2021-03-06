﻿#include "COpenGLExtension.h"

#include "GL/glext.h"
#include "COpenGLHelper.h"

const char* const OpenGLFeatureStrings[] = {
	"GL_3DFX_multisample",
	"GL_3DFX_tbuffer",
	"GL_3DFX_texture_compression_FXT1",
	"GL_AMD_draw_buffers_blend",
	"GL_AMD_performance_monitor",
	"GL_AMD_texture_texture4",
	"GL_AMD_vertex_shader_tesselator",
	"GL_APPLE_aux_depth_stencil",
	"GL_APPLE_client_storage",
	"GL_APPLE_element_array",
	"GL_APPLE_fence",
	"GL_APPLE_float_pixels",
	"GL_APPLE_flush_buffer_range",
	"GL_APPLE_object_purgeable",
	"GL_APPLE_rgb_422",
	"GL_APPLE_row_bytes",
	"GL_APPLE_specular_vector",
	"GL_APPLE_texture_range",
	"GL_APPLE_transform_hint",
	"GL_APPLE_vertex_array_object",
	"GL_APPLE_vertex_array_range",
	"GL_APPLE_vertex_program_evaluators",
	"GL_APPLE_ycbcr_422",
	"GL_ARB_color_buffer_float",
	"GL_ARB_compatibility",
	"GL_ARB_copy_buffer",
	"GL_ARB_depth_buffer_float",
	"GL_ARB_depth_clamp",
	"GL_ARB_depth_texture",
	"GL_ARB_draw_buffers",
	"GL_ARB_draw_buffers_blend",
	"GL_ARB_draw_elements_base_vertex",
	"GL_ARB_draw_instanced",
	"GL_ARB_fragment_coord_conventions",
	"GL_ARB_fragment_program",
	"GL_ARB_fragment_program_shadow",
	"GL_ARB_fragment_shader",
	"GL_ARB_framebuffer_object",
	"GL_ARB_framebuffer_sRGB",
	"GL_ARB_geometry_shader4",
	"GL_ARB_half_float_pixel",
	"GL_ARB_half_float_vertex",
	"GL_ARB_imaging",
	"GL_ARB_instanced_arrays",
	"GL_ARB_map_buffer_range",
	"GL_ARB_matrix_palette",
	"GL_ARB_multisample",
	"GL_ARB_multitexture",
	"GL_ARB_occlusion_query",
	"GL_ARB_pixel_buffer_object",
	"GL_ARB_point_parameters",
	"GL_ARB_point_sprite",
	"GL_ARB_provoking_vertex",
	"GL_ARB_sample_shading",
	"GL_ARB_seamless_cube_map",
	"GL_ARB_shader_objects",
	"GL_ARB_shader_texture_lod",
	"GL_ARB_shading_language_100",
	"GL_ARB_shadow",
	"GL_ARB_shadow_ambient",
	"GL_ARB_sync",
	"GL_ARB_texture_border_clamp",
	"GL_ARB_texture_buffer_object",
	"GL_ARB_texture_compression",
	"GL_ARB_texture_compression_rgtc",
	"GL_ARB_texture_cube_map",
	"GL_ARB_texture_cube_map_array",
	"GL_ARB_texture_env_add",
	"GL_ARB_texture_env_combine",
	"GL_ARB_texture_env_crossbar",
	"GL_ARB_texture_env_dot3",
	"GL_ARB_texture_float",
	"GL_ARB_texture_gather",
	"GL_ARB_texture_mirrored_repeat",
	"GL_ARB_texture_multisample",
	"GL_ARB_texture_non_power_of_two",
	"GL_ARB_texture_query_lod",
	"GL_ARB_texture_rectangle",
	"GL_ARB_texture_rg",
	"GL_ARB_transpose_matrix",
	"GL_ARB_uniform_buffer_object",
	"GL_ARB_vertex_array_bgra",
	"GL_ARB_vertex_array_object",
	"GL_ARB_vertex_blend",
	"GL_ARB_vertex_buffer_object",
	"GL_ARB_vertex_program",
	"GL_ARB_vertex_shader",
	"GL_ARB_window_pos",
	"GL_ATI_draw_buffers",
	"GL_ATI_element_array",
	"GL_ATI_envmap_bumpmap",
	"GL_ATI_fragment_shader",
	"GL_ATI_map_object_buffer",
	"GL_ATI_meminfo",
	"GL_ATI_pixel_format_float",
	"GL_ATI_pn_triangles",
	"GL_ATI_separate_stencil",
	"GL_ATI_text_fragment_shader",
	"GL_ATI_texture_env_combine3",
	"GL_ATI_texture_float",
	"GL_ATI_texture_mirror_once",
	"GL_ATI_vertex_array_object",
	"GL_ATI_vertex_attrib_array_object",
	"GL_ATI_vertex_streams",
	"GL_EXT_422_pixels",
	"GL_EXT_abgr",
	"GL_EXT_bgra",
	"GL_EXT_bindable_uniform",
	"GL_EXT_blend_color",
	"GL_EXT_blend_equation_separate",
	"GL_EXT_blend_func_separate",
	"GL_EXT_blend_logic_op",
	"GL_EXT_blend_minmax",
	"GL_EXT_blend_subtract",
	"GL_EXT_clip_volume_hint",
	"GL_EXT_cmyka",
	"GL_EXT_color_subtable",
	"GL_EXT_compiled_vertex_array",
	"GL_EXT_convolution",
	"GL_EXT_coordinate_frame",
	"GL_EXT_copy_texture",
	"GL_EXT_cull_vertex",
	"GL_EXT_depth_bounds_test",
	"GL_EXT_direct_state_access",
	"GL_EXT_draw_buffers2",
	"GL_EXT_draw_instanced",
	"GL_EXT_draw_range_elements",
	"GL_EXT_fog_coord",
	"GL_EXT_framebuffer_blit",
	"GL_EXT_framebuffer_multisample",
	"GL_EXT_framebuffer_object",
	"GL_EXT_framebuffer_sRGB",
	"GL_EXT_geometry_shader4",
	"GL_EXT_gpu_program_parameters",
	"GL_EXT_gpu_shader4",
	"GL_EXT_histogram",
	"GL_EXT_index_array_formats",
	"GL_EXT_index_func",
	"GL_EXT_index_material",
	"GL_EXT_index_texture",
	"GL_EXT_light_texture",
	"GL_EXT_misc_attribute",
	"GL_EXT_multi_draw_arrays",
	"GL_EXT_multisample",
	"GL_EXT_packed_depth_stencil",
	"GL_EXT_packed_float",
	"GL_EXT_packed_pixels",
	"GL_EXT_paletted_texture",
	"GL_EXT_pixel_buffer_object",
	"GL_EXT_pixel_transform",
	"GL_EXT_pixel_transform_color_table",
	"GL_EXT_point_parameters",
	"GL_EXT_polygon_offset",
	"GL_EXT_provoking_vertex",
	"GL_EXT_rescale_normal",
	"GL_EXT_secondary_color",
	"GL_EXT_separate_shader_objects",
	"GL_EXT_separate_specular_color",
	"GL_EXT_shadow_funcs",
	"GL_EXT_shared_texture_palette",
	"GL_EXT_stencil_clear_tag",
	"GL_EXT_stencil_two_side",
	"GL_EXT_stencil_wrap",
	"GL_EXT_subtexture",
	"GL_EXT_texture",
	"GL_EXT_texture3D",
	"GL_EXT_texture_array",
	"GL_EXT_texture_buffer_object",
	"GL_EXT_texture_compression_latc",
	"GL_EXT_texture_compression_rgtc",
	"GL_EXT_texture_compression_s3tc",
	"GL_EXT_texture_cube_map",
	"GL_EXT_texture_env_add",
	"GL_EXT_texture_env_combine",
	"GL_EXT_texture_env_dot3",
	"GL_EXT_texture_filter_anisotropic",
	"GL_EXT_texture_integer",
	"GL_EXT_texture_lod_bias",
	"GL_EXT_texture_mirror_clamp",
	"GL_EXT_texture_object",
	"GL_EXT_texture_perturb_normal",
	"GL_EXT_texture_shared_exponent",
	"GL_EXT_texture_snorm",
	"GL_EXT_texture_sRGB",
	"GL_EXT_texture_swizzle",
	"GL_EXT_timer_query",
	"GL_EXT_transform_feedback",
	"GL_EXT_vertex_array",
	"GL_EXT_vertex_array_bgra",
	"GL_EXT_vertex_shader",
	"GL_EXT_vertex_weighting",
	"GL_FfdMaskSGIX",
	"GL_GREMEDY_frame_terminator",
	"GL_GREMEDY_string_marker",
	"GL_HP_convolution_border_modes",
	"GL_HP_image_transform",
	"GL_HP_occlusion_test",
	"GL_HP_texture_lighting",
	"GL_IBM_cull_vertex",
	"GL_IBM_multimode_draw_arrays",
	"GL_IBM_rasterpos_clip",
	"GL_IBM_texture_mirrored_repeat",
	"GL_IBM_vertex_array_lists",
	"GL_INGR_blend_func_separate",
	"GL_INGR_color_clamp",
	"GL_INGR_interlace_read",
	"GL_INGR_palette_buffer",
	"GL_INTEL_parallel_arrays",
	"GL_INTEL_texture_scissor",
	"GL_MESA_pack_invert",
	"GL_MESA_resize_buffers",
	"GL_MESA_window_pos",
	"GL_MESAX_texture_stack",
	"GL_MESA_ycbcr_texture",
	"GL_NV_blend_square",
	"GL_NV_conditional_render",
	"GL_NV_copy_depth_to_color",
	"GL_NV_copy_image",
	"GL_NV_depth_buffer_float",
	"GL_NV_depth_clamp",
	"GL_NV_evaluators",
	"GL_NV_explicit_multisample",
	"GL_NV_fence",
	"GL_NV_float_buffer",
	"GL_NV_fog_distance",
	"GL_NV_fragment_program",
	"GL_NV_fragment_program2",
	"GL_NV_fragment_program4",
	"GL_NV_fragment_program_option",
	"GL_NV_framebuffer_multisample_coverage",
	"GL_NV_geometry_program4",
	"GL_NV_geometry_shader4",
	"GL_NV_gpu_program4",
	"GL_NV_half_float",
	"GL_NV_light_max_exponent",
	"GL_NV_multisample_filter_hint",
	"GL_NV_occlusion_query",
	"GL_NV_packed_depth_stencil",
	"GL_NV_parameter_buffer_object",
	"GL_NV_parameter_buffer_object2",
	"GL_NV_pixel_data_range",
	"GL_NV_point_sprite",
	"GL_NV_present_video",
	"GL_NV_primitive_restart",
	"GL_NV_register_combiners",
	"GL_NV_register_combiners2",
	"GL_NV_shader_buffer_load",
	"GL_NV_texgen_emboss",
	"GL_NV_texgen_reflection",
	"GL_NV_texture_barrier",
	"GL_NV_texture_compression_vtc",
	"GL_NV_texture_env_combine4",
	"GL_NV_texture_expand_normal",
	"GL_NV_texture_rectangle",
	"GL_NV_texture_shader",
	"GL_NV_texture_shader2",
	"GL_NV_texture_shader3",
	"GL_NV_transform_feedback",
	"GL_NV_transform_feedback2",
	"GL_NV_vertex_array_range",
	"GL_NV_vertex_array_range2",
	"GL_NV_vertex_buffer_unified_memory",
	"GL_NV_vertex_program",
	"GL_NV_vertex_program1_1",
	"GL_NV_vertex_program2",
	"GL_NV_vertex_program2_option",
	"GL_NV_vertex_program3",
	"GL_NV_vertex_program4",
	"GL_NV_video_capture",
	"GL_OES_read_format",
	"GL_OML_interlace",
	"GL_OML_resample",
	"GL_OML_subsample",
	"GL_PGI_misc_hints",
	"GL_PGI_vertex_hints",
	"GL_REND_screen_coordinates",
	"GL_S3_s3tc",
	"GL_SGI_color_matrix",
	"GL_SGI_color_table",
	"GL_SGI_depth_pass_instrument",
	"GL_SGIS_detail_texture",
	"GL_SGIS_fog_function",
	"GL_SGIS_generate_mipmap",
	"GL_SGIS_multisample",
	"GL_SGIS_pixel_texture",
	"GL_SGIS_point_line_texgen",
	"GL_SGIS_point_parameters",
	"GL_SGIS_sharpen_texture",
	"GL_SGIS_texture4D",
	"GL_SGIS_texture_border_clamp",
	"GL_SGIS_texture_color_mask",
	"GL_SGIS_texture_edge_clamp",
	"GL_SGIS_texture_filter4",
	"GL_SGIS_texture_lod",
	"GL_SGIS_texture_select",
	"GL_SGI_texture_color_table",
	"GL_SGIX_async",
	"GL_SGIX_async_histogram",
	"GL_SGIX_async_pixel",
	"GL_SGIX_blend_alpha_minmax",
	"GL_SGIX_calligraphic_fragment",
	"GL_SGIX_clipmap",
	"GL_SGIX_convolution_accuracy",
	"GL_SGIX_depth_pass_instrument",
	"GL_SGIX_depth_texture",
	"GL_SGIX_flush_raster",
	"GL_SGIX_fog_offset",
	"GL_SGIX_fog_scale",
	"GL_SGIX_fragment_lighting",
	"GL_SGIX_framezoom",
	"GL_SGIX_igloo_interface",
	"GL_SGIX_impact_pixel_texture",
	"GL_SGIX_instruments",
	"GL_SGIX_interlace",
	"GL_SGIX_ir_instrument1",
	"GL_SGIX_list_priority",
	"GL_SGIX_pixel_texture",
	"GL_SGIX_pixel_tiles",
	"GL_SGIX_polynomial_ffd",
	"GL_SGIX_reference_plane",
	"GL_SGIX_resample",
	"GL_SGIX_scalebias_hint",
	"GL_SGIX_shadow",
	"GL_SGIX_shadow_ambient",
	"GL_SGIX_sprite",
	"GL_SGIX_subsample",
	"GL_SGIX_tag_sample_buffer",
	"GL_SGIX_texture_add_env",
	"GL_SGIX_texture_coordinate_clamp",
	"GL_SGIX_texture_lod_bias",
	"GL_SGIX_texture_multi_buffer",
	"GL_SGIX_texture_scale_bias",
	"GL_SGIX_texture_select",
	"GL_SGIX_vertex_preclip",
	"GL_SGIX_ycrcb",
	"GL_SGIX_ycrcba",
	"GL_SGIX_ycrcb_subsample",
	"GL_SUN_convolution_border_modes",
	"GL_SUN_global_alpha",
	"GL_SUN_mesh_array",
	"GL_SUN_slice_accum",
	"GL_SUN_triangle_list",
	"GL_SUN_vertex",
	"GL_SUNX_constant_data",
	"GL_WIN_phong_shading",
	"GL_WIN_specular_fog"
};

COpenGLExtension::COpenGLExtension()
{
	MaxLights = 4;
	MaxTextureLODBias = 0.0f;
	MaxUserClipPlanes = 4;

	MaxTextureUnits = 1;
	MaxAnisotropy = 1;
	MaxMultiSample = 0;
	MaxMultipleRTs = 0;
	MaxTextureSize = 1;
	Version = 0;
	ShaderLanguageVersion = 0;
	MaxVertexShaderConst = 0;
	MaxPixelShaderConst = 0;

	TextureCompressionS3 = false;
	TextureCompressionLA = false;
	TextureCompressionRG = false;
	TextureCompressionPVR = false;
	TextureCompressionPVR2 = false;
	TextureCompressionETC1 = false;
	TextureCompressionATC = false;
	TextureCompression3DC = false;

	TextureCompression = false;
	MultisampleSupported = false;
	DiscardFrameSupported = false;
	DrawBuffersSupported = false;
	DrawBuffersBlend = false;

	memset(FeatureAvailable, 0, sizeof(FeatureAvailable));

	DimAliasedLine[0] = 1.f;
	DimAliasedLine[1] = 1.f;
	DimAliasedPoint[0] = 1.f;
	DimAliasedPoint[1] = 1.f;

	// get multitexturing function pointers
	pGlActiveTextureARB = nullptr;
	pGlClientActiveTextureARB = nullptr;
	pGlCompressedTexImage2D = nullptr;
	pGlCompressedTexSubImage2D = nullptr;

	// get fragment and vertex program function pointers
	pGlGenProgramsARB = nullptr;
	pGlGenProgramsNV = nullptr;
	pGlBindProgramARB = nullptr;
	pGlBindProgramNV = nullptr;
	pGlProgramStringARB = nullptr;
	pGlLoadProgramNV = nullptr;
	pGlDeleteProgramsARB = nullptr;
	pGlDeleteProgramsNV = nullptr;
	pGlProgramLocalParameter4fvARB = nullptr;
	pGlCreateShaderObjectARB = nullptr;
	pGlShaderSourceARB = nullptr;
	pGlCompileShaderARB = nullptr;
	pGlCreateProgramObjectARB = nullptr;
	pGlBindFragDataLocation = nullptr;
	pGlAttachObjectARB = nullptr;
	pGlLinkProgramARB = nullptr;
	pGlUseProgramObjectARB = nullptr;
	pGlDeleteObjectARB = nullptr;
	pGlGetAttachedObjectsARB = nullptr;
	pGlGetInfoLogARB = nullptr;
	pGlGetObjectParameterivARB = nullptr;
	pGlGetUniformLocationARB = nullptr;
	pGlUniform4fvARB = nullptr;
	pGlUniform1ivARB = nullptr;
	pGlUniform1fvARB = nullptr;
	pGlUniform2fvARB = nullptr;
	pGlUniform3fvARB = nullptr;
	pGlUniformMatrix2fvARB = nullptr;
	pGlUniformMatrix3fvARB = nullptr;
	pGlUniformMatrix4fvARB = nullptr;
	pGlUniformMatrix3x4 = nullptr;
	pGlGetActiveUniformARB = nullptr;

	// get point parameter extension
	pGlPointParameterfARB = nullptr;
	pGlPointParameterfvARB = nullptr;

	// get stencil extension
	pGlStencilFuncSeparate = nullptr;
	pGlStencilOpSeparate = nullptr;

	// FrameBufferObjects
	pGlBindFramebufferEXT = nullptr;
	pGlDeleteFramebuffersEXT = nullptr;
	pGlGenFramebuffersEXT = nullptr;
	pGlCheckFramebufferStatusEXT = nullptr;
	pGlFramebufferTexture2DEXT = nullptr;
	pGlBlitFramebufferEXT = nullptr;
	pGlBindRenderbufferEXT = nullptr;
	pGlDeleteRenderbuffersEXT = nullptr;
	pGlGenRenderbuffersEXT = nullptr;
	pGlRenderbufferStorageEXT = nullptr;
	pGlRenderBufferStorageMultisampleEXT = nullptr;
	pGlGetRenderBufferParameterivEXT = nullptr;
	pGlFramebufferRenderbufferEXT = nullptr;
	pGlInvalidateFramebuffer = nullptr;
	pGlDrawBuffersARB = nullptr;
	pGlDrawBuffersATI = nullptr;

	// get vertex buffer extension
	pGlGenBuffersARB = nullptr;
	pGlBindBufferARB = nullptr;
	pGlBufferDataARB = nullptr;
	pGlDeleteBuffersARB = nullptr;
	pGlBufferSubDataARB = nullptr;
	pGlGetBufferSubDataARB = nullptr;
	pGlMapBufferARB = nullptr;
	pGlUnmapBufferARB = nullptr;
	pGlIsBufferARB = nullptr;
	pGlGetBufferParameterivARB = nullptr;
	pGlGetBufferPointervARB = nullptr;
	pGlProvokingVertexARB = nullptr;
	pGlProvokingVertexEXT = nullptr;
	pGlColorMaskIndexedEXT = nullptr;
	pGlEnableIndexedEXT = nullptr;
	pGlDisableIndexedEXT = nullptr;
	pGlProgramParameteriARB = nullptr;
	pGlProgramParameteriEXT = nullptr;

	pGlDrawRangeElements = nullptr;
	pGlDrawElementsBaseVertex = nullptr;
	pGlDrawRangeElementsBaseVertex = nullptr;

	pGlGetProgramBinary = nullptr;
	pGlProgramBinary = nullptr;

	//vao
	pGlGenVertexArrays = nullptr;
	pGlDeleteVertexArrays = nullptr;
	pGlBindVertexArray = nullptr;
	pGlEnableVertexAttribArrayARB = nullptr;
	pGlDisableVertexAttribArrayARB = nullptr;
	pGlVertexAttribPointerARB = nullptr;
	pGlGetAttribLocationARB = nullptr;

	pGlTexImage2DMultisample = nullptr;
}

COpenGLExtension::~COpenGLExtension()
{
}

bool COpenGLExtension::initExtensions()
{
	const float ogl_ver = fast_atof(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	Version = static_cast<uint16_t>(floor32_(ogl_ver) * 100 + round32_(fract_(ogl_ver)*10.0f));

	PFNGLGETSTRINGIPROC pGlGetStringi = (PFNGLGETSTRINGIPROC)getProcAddress("glGetStringi");

	if (pGlGetStringi)
	{
		GLint num;
		glGetIntegerv(GL_NUM_EXTENSIONS, &num);

		for (int i = 0; i < num; ++i)
		{
			const char* str = (const char*)pGlGetStringi(GL_EXTENSIONS, i);
			for (int j = 0; j < IRR_OpenGL_Feature_Count; ++j)
			{
				if (!strcmp(OpenGLFeatureStrings[j], str))
				{
					FeatureAvailable[j] = true;
					break;
				}
			}
		}
	}
	else
	{
		const char* t = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));
		if (!t)
		{
			ASSERT(false);
			return false;
		}
		uint32_t len = (uint32_t)strlen(t);
		char * str = new char[len + 1];

		char* p = str;

		for (uint32_t i = 0; i < len; ++i)
		{
			str[i] = static_cast<char>(t[i]);

			if (str[i] == ' ')
			{
				str[i] = 0;
				for (uint32_t j = 0; j < IRR_OpenGL_Feature_Count; ++j)
				{
					if (!strcmp(OpenGLFeatureStrings[j], p))
					{
						FeatureAvailable[j] = true;
						break;
					}
				}

				p = p + strlen(p) + 1;
			}
		}

		delete[] str;
	}

	//
	initExtFunctions();

	GLint num;

	TextureCompressionS3 = FeatureAvailable[IRR_EXT_texture_compression_s3tc];
	TextureCompressionLA = FeatureAvailable[IRR_EXT_texture_compression_latc];
	TextureCompressionRG = FeatureAvailable[IRR_ARB_texture_compression_rgtc] || FeatureAvailable[IRR_EXT_texture_compression_rgtc];

	TextureCompression = TextureCompressionS3 ||
		TextureCompressionPVR ||
		TextureCompressionPVR2 ||
		TextureCompressionETC1 ||
		TextureCompressionATC ||
		TextureCompression3DC;

	MultisampleSupported = FeatureAvailable[IRR_EXT_framebuffer_multisample] && FeatureAvailable[IRR_ARB_texture_multisample];

	DiscardFrameSupported = pGlInvalidateFramebuffer != nullptr;

	DrawBuffersSupported = FeatureAvailable[IRR_ARB_draw_buffers];
	DrawBuffersBlend = FeatureAvailable[IRR_ARB_draw_buffers_blend];

	if (DrawBuffersSupported)
	{
		glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &num);
		MaxMultipleRTs = static_cast<uint8_t>(num);
	}

	if (Version > 102 || FeatureAvailable[IRR_ARB_multitexture])
	{
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &num);
		MaxTextureUnits = static_cast<uint8_t>(num);
	}

	glGetIntegerv(GL_MAX_LIGHTS, &num);
	MaxLights = static_cast<uint8_t>(num);

	if (FeatureAvailable[IRR_EXT_texture_filter_anisotropic])
	{
		glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &num);
		MaxAnisotropy = static_cast<uint8_t>(num);
	}

	if (FeatureAvailable[IRR_EXT_framebuffer_multisample])
	{
		glGetIntegerv(GL_MAX_COLOR_TEXTURE_SAMPLES, &num);
		MaxMultiSample = num;
	}

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &num);
	MaxTextureSize = max_(static_cast<uint32_t>(num), 2048u);

	if (FeatureAvailable[IRR_EXT_texture_lod_bias])
		glGetFloatv(GL_MAX_TEXTURE_LOD_BIAS_EXT, &MaxTextureLODBias);

	glGetIntegerv(GL_MAX_CLIP_PLANES, &num);
	MaxUserClipPlanes = static_cast<uint8_t>(num);

	glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, DimAliasedLine);
	glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, DimAliasedPoint);

	if (FeatureAvailable[IRR_ARB_shading_language_100] || Version >= 200)
	{
		glGetError(); // clean error buffer

		const GLubyte* shaderVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
		if (glGetError() == GL_INVALID_ENUM)
			ShaderLanguageVersion = 100;
		else
		{
			const float sl_ver = fast_atof(reinterpret_cast<const char*>(shaderVersion));
			ShaderLanguageVersion = static_cast<uint16_t>(floor32_(sl_ver) * 100 + round32_(fract_(sl_ver)*10.0f));
		}
	}

	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &num);
	MaxVertexShaderConst = static_cast<uint32_t>(num);

	glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &num);
	MaxPixelShaderConst = static_cast<uint32_t>(num);

	MaxTextureUnits = min_(MaxTextureUnits, static_cast<uint8_t>(MATERIAL_MAX_TEXTURES));

	return true;
}

bool COpenGLExtension::initExtFunctions()
{
	// get multitexturing function pointers
	pGlActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)getProcAddress("glActiveTextureARB");
	pGlCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)getProcAddress("glCompressedTexImage2D");
	pGlCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)getProcAddress("glCompressedTexSubImage2D");

	// get fragment and vertex program function pointers
	pGlGenProgramsARB = (PFNGLGENPROGRAMSARBPROC)getProcAddress("glGenProgramsARB");
	pGlGenProgramsNV = (PFNGLGENPROGRAMSNVPROC)getProcAddress("glGenProgramsNV");
	pGlBindProgramARB = (PFNGLBINDPROGRAMARBPROC)getProcAddress("glBindProgramARB");
	pGlBindProgramNV = (PFNGLBINDPROGRAMNVPROC)getProcAddress("glBindProgramNV");
	pGlProgramStringARB = (PFNGLPROGRAMSTRINGARBPROC)getProcAddress("glProgramStringARB");
	pGlLoadProgramNV = (PFNGLLOADPROGRAMNVPROC)getProcAddress("glLoadProgramNV");
	pGlDeleteProgramsARB = (PFNGLDELETEPROGRAMSARBPROC)getProcAddress("glDeleteProgramsARB");
	pGlDeleteProgramsNV = (PFNGLDELETEPROGRAMSNVPROC)getProcAddress("glDeleteProgramsNV");
	pGlProgramLocalParameter4fvARB = (PFNGLPROGRAMLOCALPARAMETER4FVARBPROC)getProcAddress("glProgramLocalParameter4fvARB");
	pGlCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC)getProcAddress("glCreateShaderObjectARB");
	pGlShaderSourceARB = (PFNGLSHADERSOURCEARBPROC)getProcAddress("glShaderSourceARB");
	pGlCompileShaderARB = (PFNGLCOMPILESHADERARBPROC)getProcAddress("glCompileShaderARB");
	pGlCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC)getProcAddress("glCreateProgramObjectARB");
	pGlBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC)getProcAddress("glBindFragDataLocation");
	pGlAttachObjectARB = (PFNGLATTACHOBJECTARBPROC)getProcAddress("glAttachObjectARB");
	pGlLinkProgramARB = (PFNGLLINKPROGRAMARBPROC)getProcAddress("glLinkProgramARB");
	pGlUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC)getProcAddress("glUseProgramObjectARB");
	pGlDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC)getProcAddress("glDeleteObjectARB");
	pGlGetAttachedObjectsARB = (PFNGLGETATTACHEDOBJECTSARBPROC)getProcAddress("glGetAttachedObjectsARB");
	pGlGetInfoLogARB = (PFNGLGETINFOLOGARBPROC)getProcAddress("glGetInfoLogARB");
	pGlGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC)getProcAddress("glGetObjectParameterivARB");
	pGlGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC)getProcAddress("glGetUniformLocationARB");
	pGlUniform4fvARB = (PFNGLUNIFORM4FVARBPROC)getProcAddress("glUniform4fvARB");
	pGlUniform1ivARB = (PFNGLUNIFORM1IVARBPROC)getProcAddress("glUniform1ivARB");
	pGlUniform1fvARB = (PFNGLUNIFORM1FVARBPROC)getProcAddress("glUniform1fvARB");
	pGlUniform2fvARB = (PFNGLUNIFORM2FVARBPROC)getProcAddress("glUniform2fvARB");
	pGlUniform3fvARB = (PFNGLUNIFORM3FVARBPROC)getProcAddress("glUniform3fvARB");
	pGlUniformMatrix2fvARB = (PFNGLUNIFORMMATRIX2FVARBPROC)getProcAddress("glUniformMatrix2fvARB");
	pGlUniformMatrix3fvARB = (PFNGLUNIFORMMATRIX3FVARBPROC)getProcAddress("glUniformMatrix3fvARB");
	pGlUniformMatrix4fvARB = (PFNGLUNIFORMMATRIX4FVARBPROC)getProcAddress("glUniformMatrix4fvARB");
	pGlUniformMatrix3x4 = (PFNGLUNIFORMMATRIX3X4FVPROC)getProcAddress("glUniformMatrix3x4fv");
	pGlGetActiveUniformARB = (PFNGLGETACTIVEUNIFORMARBPROC)getProcAddress("glGetActiveUniformARB");
	pGlProgramParameteriARB = (PFNGLPROGRAMPARAMETERIARBPROC)getProcAddress("glProgramParameteriARB");
	pGlProgramParameteriEXT = (PFNGLPROGRAMPARAMETERIEXTPROC)getProcAddress("glProgramParameteriEXT");
	pGlGetProgramBinary = (PFNGLGETPROGRAMBINARYPROC)getProcAddress("glGetProgramBinary");
	pGlProgramBinary = (PFNGLPROGRAMBINARYPROC)getProcAddress("glProgramBinary");

	// get point parameter extension
	pGlPointParameterfARB = (PFNGLPOINTPARAMETERFARBPROC)getProcAddress("glPointParameterfARB");
	pGlPointParameterfvARB = (PFNGLPOINTPARAMETERFVARBPROC)getProcAddress("glPointParameterfvARB");

	// get stencil extension
	pGlStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC)getProcAddress("glStencilFuncSeparate");
	pGlStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)getProcAddress("glStencilOpSeparate");

	// compressed textures
	pGlCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)getProcAddress("glCompressedTexImage2D");

	// FrameBufferObjects
	pGlBindFramebufferEXT = (PFNGLBINDFRAMEBUFFEREXTPROC)getProcAddress("glBindFramebufferEXT");
	pGlDeleteFramebuffersEXT = (PFNGLDELETEFRAMEBUFFERSEXTPROC)getProcAddress("glDeleteFramebuffersEXT");
	pGlGenFramebuffersEXT = (PFNGLGENFRAMEBUFFERSEXTPROC)getProcAddress("glGenFramebuffersEXT");
	pGlCheckFramebufferStatusEXT = (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)getProcAddress("glCheckFramebufferStatusEXT");
	pGlFramebufferTexture2DEXT = (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)getProcAddress("glFramebufferTexture2DEXT");
	pGlBlitFramebufferEXT = (PFNGLBLITFRAMEBUFFEREXTPROC)getProcAddress("glBlitFramebufferEXT");
	pGlBindRenderbufferEXT = (PFNGLBINDRENDERBUFFEREXTPROC)getProcAddress("glBindRenderbufferEXT");
	pGlDeleteRenderbuffersEXT = (PFNGLDELETERENDERBUFFERSEXTPROC)getProcAddress("glDeleteRenderbuffersEXT");
	pGlGenRenderbuffersEXT = (PFNGLGENRENDERBUFFERSEXTPROC)getProcAddress("glGenRenderbuffersEXT");
	pGlRenderbufferStorageEXT = (PFNGLRENDERBUFFERSTORAGEEXTPROC)getProcAddress("glRenderbufferStorageEXT");
	pGlRenderBufferStorageMultisampleEXT = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC)getProcAddress("glRenderbufferStorageMultisampleEXT");
	pGlGetRenderBufferParameterivEXT = (PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC)getProcAddress("glGetRenderbufferParameterivEXT");
	pGlFramebufferRenderbufferEXT = (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)getProcAddress("glFramebufferRenderbufferEXT");
	pGlInvalidateFramebuffer = (PFNGLINVALIDATEFRAMEBUFFERPROC)getProcAddress("glInvalidateFramebuffer");
	pGlDrawBuffersARB = (PFNGLDRAWBUFFERSARBPROC)getProcAddress("glDrawBuffersARB");
	pGlDrawBuffersATI = (PFNGLDRAWBUFFERSATIPROC)getProcAddress("glDrawBuffersATI");

	// get vertex buffer extension
	pGlGenBuffersARB = (PFNGLGENBUFFERSARBPROC)getProcAddress("glGenBuffersARB");
	pGlBindBufferARB = (PFNGLBINDBUFFERARBPROC)getProcAddress("glBindBufferARB");
	pGlBufferDataARB = (PFNGLBUFFERDATAARBPROC)getProcAddress("glBufferDataARB");
	pGlDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC)getProcAddress("glDeleteBuffersARB");
	pGlBufferSubDataARB = (PFNGLBUFFERSUBDATAARBPROC)getProcAddress("glBufferSubDataARB");
	pGlGetBufferSubDataARB = (PFNGLGETBUFFERSUBDATAARBPROC)getProcAddress("glGetBufferSubDataARB");
	pGlMapBufferARB = (PFNGLMAPBUFFERARBPROC)getProcAddress("glMapBufferARB");
	pGlUnmapBufferARB = (PFNGLUNMAPBUFFERARBPROC)getProcAddress("glUnmapBufferARB");
	pGlIsBufferARB = (PFNGLISBUFFERARBPROC)getProcAddress("glIsBufferARB");
	pGlGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC)getProcAddress("glGetBufferParameterivARB");
	pGlGetBufferPointervARB = (PFNGLGETBUFFERPOINTERVARBPROC)getProcAddress("glGetBufferPointervARB");
	pGlProvokingVertexARB = (PFNGLPROVOKINGVERTEXPROC)getProcAddress("glProvokingVertex");
	pGlProvokingVertexEXT = (PFNGLPROVOKINGVERTEXEXTPROC)getProcAddress("glProvokingVertexEXT");
	pGlColorMaskIndexedEXT = (PFNGLCOLORMASKINDEXEDEXTPROC)getProcAddress("glColorMaskIndexedEXT");
	pGlEnableIndexedEXT = (PFNGLENABLEINDEXEDEXTPROC)getProcAddress("glEnableIndexedEXT");
	pGlDisableIndexedEXT = (PFNGLDISABLEINDEXEDEXTPROC)getProcAddress("glDisableIndexedEXT");

	// draw
	pGlDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC)getProcAddress("glDrawRangeElements");
	pGlDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC)getProcAddress("glDrawElementsBaseVertex");
	pGlDrawRangeElementsBaseVertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)getProcAddress("glDrawRangeElementsBaseVertex");

	// vao
	pGlGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)getProcAddress("glGenVertexArrays");
	pGlDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)getProcAddress("glDeleteVertexArrays");
	pGlBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)getProcAddress("glBindVertexArray");
	pGlEnableVertexAttribArrayARB = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC)getProcAddress("glEnableVertexAttribArrayARB");
	pGlDisableVertexAttribArrayARB = (PFNGLDISABLEVERTEXATTRIBARRAYARBPROC)getProcAddress("glDisableVertexAttribArrayARB");
	pGlVertexAttribPointerARB = (PFNGLVERTEXATTRIBPOINTERARBPROC)getProcAddress("glVertexAttribPointerARB");
	pGlGetAttribLocationARB = (PFNGLGETATTRIBLOCATIONARBPROC)getProcAddress("glGetAttribLocationARB");

	pGlTexImage2DMultisample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC)getProcAddress("glTexImage2DMultisample");

	return true;
}

bool COpenGLExtension::queryFeature(E_VIDEO_DRIVER_FEATURE feature) const
{
	switch (feature)
	{
	case EVDF_RENDER_TO_TARGET:
		return FeatureAvailable[IRR_EXT_framebuffer_object];
	case EVDF_HARDWARE_TL:
	case EVDF_TEXTURE_ADDRESS:
	case EVDF_SEPARATE_UVWRAP:
	case  EVDF_MIP_MAP:
	case EVDF_STENCIL_BUFFER:
	case EVDF_TEXTURE_NSQUARE:
		return true;
	case EVDF_TEXTURE_NPOT:
		return FeatureAvailable[IRR_ARB_texture_non_power_of_two];
	case EVDF_COLOR_MASK:
	case EVDF_MULTIPLE_RENDER_TARGETS:
	case EVDF_MRT_BLEND:
		return true;
	case EVDF_MRT_COLOR_MASK:
		return FeatureAvailable[IRR_EXT_draw_buffers2];
	case EVDF_MRT_BLEND_FUNC:
		return FeatureAvailable[IRR_ARB_draw_buffers_blend] || FeatureAvailable[IRR_AMD_draw_buffers_blend];
	case EVDF_STREAM_OFFSET:
	case EVDF_TEXTURE_MULTISAMPLING:
		return FeatureAvailable[IRR_ARB_multisample];
	case EVDF_PIXEL_SHADER_2_0:
	case EVDF_VERTEX_SHADER_2_0:
		return (FeatureAvailable[IRR_ARB_shading_language_100] || ShaderLanguageVersion >= 200);
	case EVDF_PIXEL_SHADER_3_0:
	case EVDF_VERTEX_SHADER_3_0:
		return (FeatureAvailable[IRR_ARB_shading_language_100] || ShaderLanguageVersion >= 300);
	case EVDF_GEOMETRY_SHADER_4_0:
		return FeatureAvailable[IRR_ARB_geometry_shader4] || FeatureAvailable[IRR_EXT_geometry_shader4] || FeatureAvailable[IRR_NV_geometry_program4] || FeatureAvailable[IRR_NV_geometry_shader4];
	default:
		return false;
	}
}

void COpenGLExtension::extGlActiveTexture(GLenum texture) const
{
	if (MaxTextureUnits > 1 && pGlActiveTextureARB)
	{
		pGlActiveTextureARB(texture);
		CHECK_OPENGL_ERROR("extGlActiveTexture");
	}
}

void COpenGLExtension::extGlCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data) const
{
	pGlCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
	CHECK_OPENGL_ERROR("extGlCompressedTexImage2D");
}

void COpenGLExtension::extGlCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data) const
{
	pGlCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
	CHECK_OPENGL_ERROR("extGlCompressedTexSubImage2D");
}

/*
void COpenGLExtension::extGlGenPrograms( GLsizei n, GLuint *programs )
{
if (pGlGenProgramsARB)
{
pGlGenProgramsARB(n, programs);
CHECK_OPENGL_ERROR("extGlGenPrograms");
}
else if (pGlGenProgramsNV)
{
pGlGenProgramsNV(n, programs);
CHECK_OPENGL_ERROR("extGlGenPrograms");
}
}

void COpenGLExtension::extGlBindProgram( GLenum target, GLuint program )
{
if (pGlBindProgramARB)
{
pGlBindProgramARB(target, program);
CHECK_OPENGL_ERROR("extGlBindProgram");
}
else if (pGlBindProgramNV)
{
pGlBindProgramNV(target, program);
CHECK_OPENGL_ERROR("extGlBindProgram");
}
}

void COpenGLExtension::extGlProgramString( GLenum target, GLenum format, GLsizei len, const GLvoid *string )
{
if (pGlProgramStringARB)
{
pGlProgramStringARB(target, format, len, string);
CHECK_OPENGL_ERROR("extGlProgramString");
}
}

void COpenGLExtension::extGlLoadProgram( GLenum target, GLuint id, GLsizei len, const GLubyte *string )
{
if (pGlLoadProgramNV)
{
pGlLoadProgramNV(target, id, len, string);
CHECK_OPENGL_ERROR("extGlLoadProgram");
}
}

void COpenGLExtension::extGlDeletePrograms( GLsizei n, const GLuint *programs )
{
if (pGlDeleteProgramsARB)
{
pGlDeleteProgramsARB(n, programs);
CHECK_OPENGL_ERROR("extGlDeletePrograms");
}
else if (pGlDeleteProgramsNV)
{
pGlDeleteProgramsNV(n, programs);
CHECK_OPENGL_ERROR("extGlDeletePrograms");
}
}
*/

GLhandleARB COpenGLExtension::extGlCreateShaderObject(GLenum shaderType) const
{
	GLhandleARB ret = 0;
	ret = pGlCreateShaderObjectARB(shaderType);
	CHECK_OPENGL_ERROR("extGlCreateShaderObject");

	return ret;
}

void COpenGLExtension::extGlShaderSourceARB(GLhandleARB shader, int numOfStrings, const char **strings, int *lenOfStrings) const
{
	pGlShaderSourceARB(shader, numOfStrings, strings, lenOfStrings);
	CHECK_OPENGL_ERROR("extGlShaderSourceARB");
}

void COpenGLExtension::extGlCompileShaderARB(GLhandleARB shader) const
{
	pGlCompileShaderARB(shader);
	CHECK_OPENGL_ERROR("extGlCompileShaderARB");
}

GLhandleARB COpenGLExtension::extGlCreateProgramObject(void) const
{
	GLhandleARB ret = 0;
	ret = pGlCreateProgramObjectARB();

	CHECK_OPENGL_ERROR("extGlCreateProgramObject");

	return ret;
}

void COpenGLExtension::extGlBindFragDataLocation(GLuint program, GLuint color, const char *name) const
{
	pGlBindFragDataLocation(program, color, name);

	CHECK_OPENGL_ERROR("extBindFragDataLocation");
}

void COpenGLExtension::extGlAttachObject(GLhandleARB program, GLhandleARB shader) const
{
	pGlAttachObjectARB(program, shader);
	CHECK_OPENGL_ERROR("extGlAttachObject");
}

void COpenGLExtension::extGlLinkProgramARB(GLhandleARB program) const
{
	pGlLinkProgramARB(program);
	CHECK_OPENGL_ERROR("extGlLinkProgramARB");
}
 
void COpenGLExtension::extGlUseProgramObject(GLhandleARB prog) const
{
	pGlUseProgramObjectARB(prog);
	CHECK_OPENGL_ERROR("extGlUseProgramObject");
}

void COpenGLExtension::extGlDeleteObject(GLhandleARB object) const
{
	pGlDeleteObjectARB(object);
	CHECK_OPENGL_ERROR("extGlDeleteObject");
}

void COpenGLExtension::extGlGetAttachedObjects(GLhandleARB program, GLsizei maxcount, GLsizei* count, GLhandleARB* shaders) const
{
	pGlGetAttachedObjectsARB(program, maxcount, count, shaders);
	CHECK_OPENGL_ERROR("extGlGetAttachedObjects");
}

void COpenGLExtension::extGlGetInfoLog(GLhandleARB object, GLsizei maxLength, GLsizei *length, GLcharARB *infoLog) const
{
	pGlGetInfoLogARB(object, maxLength, length, infoLog);
	CHECK_OPENGL_ERROR("extGlGetInfoLog");
}

void COpenGLExtension::extGlGetObjectParameteriv(GLhandleARB object, GLenum type, GLint *param) const
{
	pGlGetObjectParameterivARB(object, type, param);
	CHECK_OPENGL_ERROR("extGlGetObjectParameteriv");
}

GLint COpenGLExtension::extGlGetUniformLocationARB(GLhandleARB program, const char *name) const
{
	GLint ret = 0;
	ret = pGlGetUniformLocationARB(program, name);
	CHECK_OPENGL_ERROR("extGlGetUniformLocationARB");

	return ret;
}

void COpenGLExtension::extGlUniform4fv(GLint location, GLsizei count, const GLfloat *v) const
{
	pGlUniform4fvARB(location, count, v);
	CHECK_OPENGL_ERROR("extGlUniform4fv");
}

void COpenGLExtension::extGlUniform1iv(GLint loc, GLsizei count, const GLint *v) const
{
	pGlUniform1ivARB(loc, count, v);
	CHECK_OPENGL_ERROR("extGlUniform1iv");
}

void COpenGLExtension::extGlUniform1fv(GLint loc, GLsizei count, const GLfloat *v) const
{
	pGlUniform1fvARB(loc, count, v);
	CHECK_OPENGL_ERROR("extGlUniform1fv");
}

void COpenGLExtension::extGlUniform2fv(GLint loc, GLsizei count, const GLfloat *v) const
{
	pGlUniform2fvARB(loc, count, v);
	CHECK_OPENGL_ERROR("extGlUniform2fv");
}

void COpenGLExtension::extGlUniform3fv(GLint loc, GLsizei count, const GLfloat *v) const
{
	pGlUniform3fvARB(loc, count, v);
	CHECK_OPENGL_ERROR("extGlUniform3fv");
}

void COpenGLExtension::extGlUniformMatrix2fv(GLint loc, GLsizei count, GLboolean transpose, const GLfloat *v) const
{
	pGlUniformMatrix2fvARB(loc, count, transpose, v);
	CHECK_OPENGL_ERROR("extGlUniformMatrix2fv");
}

void COpenGLExtension::extGlUniformMatrix3fv(GLint loc, GLsizei count, GLboolean transpose, const GLfloat *v) const
{
	pGlUniformMatrix3fvARB(loc, count, transpose, v);
	CHECK_OPENGL_ERROR("extGlUniformMatrix3fv");
}

void COpenGLExtension::extGlUniformMatrix4fv(GLint loc, GLsizei count, GLboolean transpose, const GLfloat *v) const
{
	pGlUniformMatrix4fvARB(loc, count, transpose, v);
	CHECK_OPENGL_ERROR("extGlUniformMatrix4fv");
}

void COpenGLExtension::extGlGetActiveUniformARB(GLhandleARB program, GLuint index, GLsizei maxlength, GLsizei *length, GLint *size, GLenum *type, GLcharARB *name) const
{
	pGlGetActiveUniformARB(program, index, maxlength, length, size, type, name);
	CHECK_OPENGL_ERROR("extGlGetActiveUniformARB");
}

void COpenGLExtension::extGlBindFramebuffer(GLenum target, GLuint framebuffer) const
{
	pGlBindFramebufferEXT(target, framebuffer);
	CHECK_OPENGL_ERROR("extGlBindFramebuffer");
}

void COpenGLExtension::extGlDeleteFramebuffers(GLsizei n, const GLuint *framebuffers) const
{
	pGlDeleteFramebuffersEXT(n, framebuffers);
	CHECK_OPENGL_ERROR("extGlDeleteFramebuffers");
}

void COpenGLExtension::extGlGenFramebuffers(GLsizei n, GLuint *framebuffers) const
{
	pGlGenFramebuffersEXT(n, framebuffers);
	CHECK_OPENGL_ERROR("extGlGenFramebuffers");
}

GLenum COpenGLExtension::extGlCheckFramebufferStatus(GLenum target) const
{
	GLenum ret = 0;
	ret = pGlCheckFramebufferStatusEXT(target);
	CHECK_OPENGL_ERROR("extGlCheckFramebufferStatus");

	return ret;
}

void COpenGLExtension::extGlFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) const
{
	pGlFramebufferTexture2DEXT(target, attachment, textarget, texture, level);
	CHECK_OPENGL_ERROR("extGlFramebufferTexture2D");
}

void COpenGLExtension::extGlBlitFramebufferEXT(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) const
{
	pGlBlitFramebufferEXT(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
	CHECK_OPENGL_ERROR("extGlBlitFramebufferEXT");
}

void COpenGLExtension::extGlBindRenderbuffer(GLenum target, GLuint renderbuffer) const
{
	pGlBindRenderbufferEXT(target, renderbuffer);
	CHECK_OPENGL_ERROR("extGlBindRenderbuffer");
}

void COpenGLExtension::extGlDeleteRenderbuffers(GLsizei n, const GLuint *renderbuffers) const
{
	pGlDeleteRenderbuffersEXT(n, renderbuffers);
	CHECK_OPENGL_ERROR("extGlDeleteRenderbuffers");
}

void COpenGLExtension::extGlGenRenderbuffers(GLsizei n, GLuint *renderbuffers) const
{
	pGlGenRenderbuffersEXT(n, renderbuffers);
	CHECK_OPENGL_ERROR("extGlGenRenderbuffers");
}

void COpenGLExtension::extGlRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) const
{
	pGlRenderbufferStorageEXT(target, internalformat, width, height);
	CHECK_OPENGL_ERROR("extGlRenderbufferStorage");
}

void COpenGLExtension::extGlRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) const
{
	pGlRenderBufferStorageMultisampleEXT(target, samples, internalformat, width, height);
	CHECK_OPENGL_ERROR("extGlRenderbufferStorageMultisample");
}

void COpenGLExtension::extGlGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint *params) const
{
	pGlGetRenderBufferParameterivEXT(target, pname, params);
	CHECK_OPENGL_ERROR("extGlGetRenderbufferParameteriv");
}

void COpenGLExtension::extGlFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) const
{
	pGlFramebufferRenderbufferEXT(target, attachment, renderbuffertarget, renderbuffer);
	CHECK_OPENGL_ERROR("extGlFramebufferRenderbuffer");
}

void COpenGLExtension::extGlInvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments) const
{
	pGlInvalidateFramebuffer(target, numAttachments, attachments);
	CHECK_OPENGL_ERROR("extGlInvalidateFrameBuffer");
}

void COpenGLExtension::extGlDrawBuffers(GLsizei n, const GLenum *bufs) const
{
	if (pGlDrawBuffersARB)
		pGlDrawBuffersARB(n, bufs);
	else if (pGlDrawBuffersATI)
		pGlDrawBuffersATI(n, bufs);
	CHECK_OPENGL_ERROR("extGlDrawBuffers");
}

void COpenGLExtension::extGlGenBuffers(GLsizei n, GLuint *buffers) const
{
	pGlGenBuffersARB(n, buffers);
	CHECK_OPENGL_ERROR("extGlGenBuffers");
}

void COpenGLExtension::extGlBindBuffer(GLenum target, GLuint buffer) const
{
	pGlBindBufferARB(target, buffer);
	CHECK_OPENGL_ERROR("extGlBindBuffer");
}

void COpenGLExtension::extGlBufferData(GLenum target, GLsizeiptrARB size, const GLvoid *data, GLenum usage) const 
{
	pGlBufferDataARB(target, size, data, usage);
	CHECK_OPENGL_ERROR("extGlBufferData");
}

void COpenGLExtension::extGlDeleteBuffers(GLsizei n, const GLuint *buffers) const
{
	pGlDeleteBuffersARB(n, buffers);
	CHECK_OPENGL_ERROR("extGlDeleteBuffers");
}

void COpenGLExtension::extGlBufferSubData(GLenum target, GLintptrARB offset, GLsizeiptrARB size, const GLvoid *data) const
{
	pGlBufferSubDataARB(target, offset, size, data);
	CHECK_OPENGL_ERROR("extGlBufferSubData");
}

void COpenGLExtension::extGlDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices) const
{
	glDrawElements(mode, count, type, indices);
	CHECK_OPENGL_ERROR("extGlDrawElements");
}

void COpenGLExtension::extGlDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices) const
{
	pGlDrawRangeElements(mode, start, end, count, type, indices);
	CHECK_OPENGL_ERROR("extGlDrawRangeElements");
}

void COpenGLExtension::extGlDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLint basevertex) const
{
	pGlDrawElementsBaseVertex(mode, count, type, indices, basevertex);
	CHECK_OPENGL_ERROR("extGlDrawElementsBaseVertex");
}

void COpenGLExtension::extGlDrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices, GLint basevertex) const
{
	pGlDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
	CHECK_OPENGL_ERROR("extGlDrawRangeElementsBaseVertex");
}

void COpenGLExtension::extGlGenVertexArrays(GLsizei n, GLuint *arrays) const
{
	pGlGenVertexArrays(n, arrays);
	CHECK_OPENGL_ERROR("extGlGenVertexArrays");
}

void COpenGLExtension::extGlDeleteVertexArrays(GLsizei n, const GLuint *arrays) const
{
	pGlDeleteVertexArrays(n, arrays);
	CHECK_OPENGL_ERROR("extGlDeleteVertexArrays");
}

void COpenGLExtension::extGlBindVertexArray(GLuint array) const
{
	pGlBindVertexArray(array);
	CHECK_OPENGL_ERROR("extGlBindVertexArray");
}

void COpenGLExtension::extGlEnableVertexAttribArrayARB(GLuint index) const
{
	pGlEnableVertexAttribArrayARB(index);
	CHECK_OPENGL_ERROR("extGlEnableVertexAttribArrayARB");
}

void COpenGLExtension::extGlDisableVertexAttribArrayARB(GLuint index) const
{
	pGlDisableVertexAttribArrayARB(index);
	CHECK_OPENGL_ERROR("extGlDisableVertexAttribArrayARB");
}

void COpenGLExtension::extGlVertexAttribPointerARB(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer) const
{
	pGlVertexAttribPointerARB(index, size, type, normalized, stride, pointer);
	CHECK_OPENGL_ERROR("extGlVertexAttribPointerARB");
}

GLint COpenGLExtension::extGlGetAttribLocationARB(GLhandleARB programObj, const GLcharARB *name) const
{
	GLint v = pGlGetAttribLocationARB(programObj, name);
	CHECK_OPENGL_ERROR("extGlGetAttribLocationARB");
	return v;
}

void COpenGLExtension::extGlTexImage2DMultisample(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) const
{
	pGlTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
	CHECK_OPENGL_ERROR("extGlTexImage2DMultisample");
}

void* COpenGLExtension::getProcAddress(const char* funcname) const
{
	PROC p = wglGetProcAddress(funcname);
	if (!p)
	{
		ASSERT(false);
	}
	return p;
}

bool COpenGLExtension::canUseVAO() const
{
	return ShaderLanguageVersion >= 303 && queryOpenGLFeature(IRR_ARB_vertex_array_object);
}

bool COpenGLExtension::checkFBOStatus() const
{
	if (!queryOpenGLFeature(IRR_EXT_framebuffer_object))
		return false;

	GLenum status = extGlCheckFramebufferStatus(GL_FRAMEBUFFER);

	switch (status)
	{
		//Our FBO is perfect, return true
	case GL_FRAMEBUFFER_COMPLETE_EXT:
		return true;

	case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
		ASSERT(false);
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
		ASSERT(false);
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
		ASSERT(false);
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
		ASSERT(false);
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
		ASSERT(false);
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
		ASSERT(false);
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT:
		ASSERT(false);
		break;

	case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
		ASSERT(false);
		break;

	default:
		ASSERT(false);
		break;
	}

	return false;
}

