﻿#ifndef __MMD_VMD_ANIMATION_H__
#define __MMD_VMD_ANIMATION_H__

#include "main.h"
#include "MMD_PMX_Control.h"
#include "EncodingConversion.h"
#include "description/PMX_Bone_Tag.h"
#include "description/VMD_Cam_Obj.h"

namespace mmd{

	struct VMD_Camera_import_settings
	{
		Float PositionMultiple = 8.5;
		Float TimeOffset = 0;
		Filename fn = Filename();
		BaseDocument* doc = nullptr;
	};
	struct VMD_Camera_export_settings
	{
		Float PositionMultiple = 8.5;
		Float TimeOffset = 0;
		Int32 use_rotation = 0;
	};
	struct VMD_Conversion_Camera_settings {
		Float distance = 0;
		Int32 use_rotation = 0;
		BaseObject* str_cam = nullptr;
	}; 
	struct VMD_Motions_import_settings {
		Float PositionMultiple = 8.5;
		Float TimeOffset = 0;
		Bool QuaternionRotationSW = true;
		Bool DetailReport = false;
		Bool ByTag = true;
	};
	struct VMD_Motions_export_settings {
		Float PositionMultiple = 8.5;
		Float TimeOffset = 0;
		Bool QuaternionRotationSW;
		Bool DetailReport;
		Bool ByTag;
	};
	class VMDAnimation
	{
	private:
		class VMDMotionSortedArray : public maxon::SortedArray<VMDMotionSortedArray, maxon::PointerArray<VMD_Motion>>
		{
		public:
			static Bool LessThan(const VMD_Motion& a, const VMD_Motion& b) { return a.frame_no < b.frame_no; }
			static Bool IsEqual(const VMD_Motion& a, const VMD_Motion& b) { return a.frame_no == b.frame_no; }
		};

		class VMDMorphSortedArray : public maxon::SortedArray<VMDMorphSortedArray, maxon::PointerArray<VMD_Morph>>
		{
		public:
			static Bool LessThan(const VMD_Morph& a, const VMD_Morph& b) { return a.frame_no < b.frame_no; }
			static Bool IsEqual(const VMD_Morph& a, const VMD_Morph& b) { return a.frame_no == b.frame_no; }
		};

		class VMDCameraSortedArray : public maxon::SortedArray<VMDCameraSortedArray, maxon::PointerArray<VMD_Camera>>
		{
		public:
			static Bool LessThan(const VMD_Camera& a, const VMD_Camera& b) { return a.frame_no < b.frame_no; }
			static Bool IsEqual(const VMD_Camera& a, const VMD_Camera& b) { return a.frame_no == b.frame_no; }
		};

		class VMDLightSortedArray : public maxon::SortedArray<VMDLightSortedArray, maxon::PointerArray<VMD_Light>>
		{
		public:
			static Bool LessThan(const VMD_Light& a, const VMD_Light& b) { return a.frame_no < b.frame_no; }
			static Bool IsEqual(const VMD_Light& a, const VMD_Light& b) { return a.frame_no == b.frame_no; }
		};
		//最初使用动作模型名称
		String ModelName;
		//是否为摄像机动作
		Bool IsCamera = false;
		//动作关键帧数量
		UInt32 MotionFrameNumber = 0;
		//表情关键帧数量
		UInt32 MorphFrameNumber = 0;
		//摄像机关键帧数量
		UInt32 CameraFrameNumber = 0;
		//灯光关键帧数量
		UInt32 LightFrameNumber = 0;
		//动作数据数组
		VMDMotionSortedArray motion_frames;
		//表情动画数据数组
		VMDMorphSortedArray morph_frames;
		//摄像机数据数组
		VMDCameraSortedArray camera_frames;
		//灯光数据数组
		VMDLightSortedArray light_frames;
	public:
		//构造函数
		VMDAnimation(){}
		//析构函数
		~VMDAnimation();

		//用于从文件导入到对象
		maxon::Result<void> LoadFromFile(BaseFile* const file);
		//用于将对象保存到文件
		maxon::Result<void> WriteToFile(BaseFile* const file);

		//从文件导入摄像机数据
		static maxon::Result<void> FromFileImportCamera(VMD_Camera_import_settings setting);
		//从项目导出摄像机数据
		static maxon::Result<void> FromDocumentExportCamera(VMD_Camera_export_settings setting);
		//从文件导入动作或表情数据
		static maxon::Result<void> FromFileImportMotions(VMD_Motions_import_settings setting);
	};

	class VMD_Cam_Obj : public ObjectData
	{		
	private:
		//使用Map储存补间曲线数据
		maxon::HashMap<Int32, VMD_Curve*> XCurve;
		maxon::HashMap<Int32, VMD_Curve*> YCurve;
		maxon::HashMap<Int32, VMD_Curve*> ZCurve;
		maxon::HashMap<Int32, VMD_Curve*> RCurve;
		maxon::HashMap<Int32, VMD_Curve*> DCurve;
		maxon::HashMap<Int32, VMD_Curve*> VCurve;
		maxon::HashMap<Int32, VMD_Curve*> ACurve;	
		//析构函数
		~VMD_Cam_Obj() {}		
		//储存前一帧，以确定更新状态
		Int32 prev_frame = -1;
		//储存上一种曲线类型，以确定更新状态
		Int32 prev_curve_type = -1;
		//管理的摄像机对象
		BaseObject* cam = nullptr;
		INSTANCEOF(VMD_Cam_Obj, ObjectData)

	public:		
		// 用于限制SplineData的回调函数
		static Bool SplineDataCallBack(Int32 cid, const void* data);
		//将普通摄像机转换为MMD摄像机
		static maxon::Result<BaseObject*> ConversionCamera(VMD_Conversion_Camera_settings setting);
		//获取曲线值
		Bool GetCurve(Int32 type, Int32 frame_on, VMD_Curve* curve);
		//设置曲线值
		Bool SetCurve(Int32 type, Int32 frame_on, VMD_Curve* curve);
		//更新补间曲线
		Bool UpdateCurve(Int32 frame_on);
		//更新全部补间曲线
		Bool UpdateAllCurve();
		//获取对象管理的摄像机对象
		BaseObject* GetCamera() { return cam; }
		//初始化摄像机对象
		inline Bool CameraInit();
		//初始化曲线
		inline Bool CurveInit();

		//对象初始化
		virtual Bool Init(GeListNode* node);
		//设置参数时调用，用于调用SplineData的回调函数
		virtual Bool SetDParameter(GeListNode* node, const DescID& id, const GeData& t_data, DESCFLAGS_SET& flags);
		//禁用与启用参数
		virtual Bool GetDEnabling(GeListNode* node, const DescID& id, const GeData& t_data, DESCFLAGS_ENABLE flags, const BaseContainer* itemdesc);
		//接收Message时调用，用于处理事件
		virtual Bool Message(GeListNode* node, Int32 type, void* data);	
		//实时调用
		virtual EXECUTIONRESULT Execute(BaseObject* op, BaseDocument* doc, BaseThread* bt, Int32 priority, EXECUTIONFLAGS flags);
		//将实时调用添加入优先级列表
		virtual Bool AddToExecution(BaseObject* op, PriorityList* list);
		//删除函数
		virtual void Free(GeListNode* node);
		//生成函数
		static NodeData* Alloc() { return NewObjClear(VMD_Cam_Obj); }
	};

	class VMDLoaderData : public SceneLoaderData
	{
		Bool IsCamera = 0;
		class VMDLoaderCameraDialog : public GeDialog
		{
			ImagesGUI* Images = nullptr;
			Filename fn;
			BaseDocument* doc = nullptr;
		public:
			VMDLoaderCameraDialog(Filename fn_, BaseDocument* doc_):fn(fn_),doc(doc_) {
			}
			virtual ~VMDLoaderCameraDialog(void) {
				delete Images;
			}

			virtual Bool CreateLayout(void)
			{

				SetTitle(GeLoadString(IDS_VMD_TOOL_TITLE));
				Images = new ImagesGUI("mmd_tool_title.png"_s, 300, 78);
				C4DGadget* userAreaGadget = this->AddUserArea(999, BFH_SCALE, SizePix(300), SizePix(78));
				if (userAreaGadget != nullptr)
					this->AttachUserArea((*Images), userAreaGadget);
				GroupBegin(1001, BFH_CENTER, 1, 2, GeLoadString(IDS_VMD_CAM_IMPORT_TITLE), 0, 0, 0);
				GroupBorder(BORDER_GROUP_IN);
				GroupBorderSpace(5, 5, 5, 10);
				GroupSpace(2, 5);

				GroupBegin(1002, BFH_LEFT, 2, 1, ""_s, 0, 350, 10);
				AddStaticText(100001, BFH_LEFT, 100, 10, GeLoadString(IDS_VMD_CAM_IMPORT_SIZE_NAME), BORDER_NONE);
				AddEditNumberArrows(100002, BFH_LEFT, 250, 10);
				GroupEnd();

				GroupBegin(1003, BFH_LEFT, 2, 1, ""_s, 0, 350, 10);
				AddStaticText(100003, BFH_LEFT, 100, 10, GeLoadString(IDS_VMD_CAM_IMPORT_OFFSET_NAME), BORDER_NONE);
				AddEditNumberArrows(100004, BFH_LEFT, 250, 10);
				GroupEnd();


				GroupBegin(1004, BFH_CENTER, 2, 1, ""_s, 0, 350, 10);
				GroupSpace(50,0);
				AddButton(100005, BFH_CENTER, 100, 30, GeLoadString(IDS_VMD_CAM_IMPORT_BUTTON));
				AddButton(100006, BFH_CENTER, 100, 30, GeLoadString(IDS_MSG_RENAME_CANCEL));
				GroupEnd();
				return true;
			}

			virtual Bool InitValues(void)
			{
				SetFloat(100002, 8.5);
				SetFloat(100004, 0);
				return true;
			}

			virtual Bool Command(Int32 id, const BaseContainer& msg)
			{
				iferr_scope;
				switch(id)
				{
				case 100005:
				{
					mmd::VMD_Camera_import_settings setting_;
					setting_.fn = fn;
					setting_.doc = doc;
					GetFloat(100002, setting_.PositionMultiple);
					GetFloat(100004, setting_.TimeOffset);
					iferr(mmd::VMDAnimation::FromFileImportCamera(setting_))
					{
						return false;
					}
					Close();
					break;
				}
				case 100006:
				{
					Close();
					break;
				}
				default:
					break;
				}
				return true;
			}
		};
	public:
		virtual Bool Identify(BaseSceneLoader* node, const Filename& name, UChar* probe, Int32 size);
		virtual FILEERROR Load(BaseSceneLoader* node, const Filename& name, BaseDocument* doc, SCENEFILTER filterflags, maxon::String* error, BaseThread* bt);
		static NodeData* Alloc() { return NewObjClear(VMDLoaderData); }
	};



	class VMD_Cam_Draw : public SceneHookData
	{	
		INSTANCEOF(VMD_Cam_Draw, SceneHookData)
	public:
		virtual Bool Draw(BaseSceneHook* node, BaseDocument* doc, BaseDraw* bd, BaseDrawHelp* bh, BaseThread* bt, SCENEHOOKDRAW flags);
		static NodeData* Alloc(void) { return NewObjClear(VMD_Cam_Draw); }
	};
} // namespace
#endif  __MMD_VMD_ANIMATION_H__