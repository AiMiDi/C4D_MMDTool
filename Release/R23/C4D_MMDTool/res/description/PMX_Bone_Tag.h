#ifndef _PMX_BONE_TAG_H_
#define _PMX_BONE_TAG_H_
enum
{
	PMX_BONE_INFO_GRP = 1000,
	BONE_NAME_LOCAL,//������������
	BONE_NAME_UNIVERSAL,//����ͨ������
	POSITION,//λ��

	PMX_BONE_PARENT_BONE_GRP,//�׹���
	PARENT_BONE_INDEX,//�׹�����
	PARENT_BONE_LINK,//�׹�

	PMX_BONE_FLAG_GRP,//����������
	ROTATABLE,//������ת
	TRANSLATABLE,//�����ƶ�
	VISIBLE,//������ʾ
	ENABLED,//���ò���
	IS_IK,//����IK��

	PMX_BONE_DEFORM_LAYER_GRP,//���νײ���
	LAYER,//���νײ�
	PHYSICS_AFTER_DEFORM,//�ȱ��Σ���������

	PMX_BONE_END_OF_BONE_GRP,//����ĩ��
	INDEXED_TAIL_POSITION,//����β��(���)λ��
	TAIL_IS_INDEX = 1,//�������ӹ���
	TAIL_IS_POSITION = 0,//���������λ��
	TAIL_INDEX = 1018,//�ӹ�������
	TAIL_POSITION,//���λ��

	PMX_BONE_INHERIT_GRP,//�����̳���
	INHERIT_ROTATION,//���ü̳��׹ǵ���ת
	INHERIT_TRANSLATION,//���ü̳��׹ǵ��ƶ�
	INHERIT_BONE_PARENT_INDEX,//�����̳�-�׹�����
	INHERIT_BONE_PARENT_INFLUENCE,//�����̳�-Ӱ��Ȩ��
	INHERIT_BONE_PARENT_LINK,//�����̳�-�׹�

	PMX_BONE_FIXED_AXIS_GRP,//������
	FIXED_AXIS,//����������
	BONE_FIXED_AXIS,//�����̶���-�᷽��

	PMX_BONE_LOCAL_COORDINATE_GRP,//Local��
	LOCAL_COORDINATE,//����Local��
	BONE_LOCAL_X,//����Local����-Xʸ��
	BONE_LOCAL_Z,//����Local����-Zʸ��
};
#endif _PMX_BONE_TAG_H_
