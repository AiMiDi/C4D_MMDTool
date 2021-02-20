#ifndef _PMX_BONE_TAG_H_
#define _PMX_BONE_TAG_H_
enum
{
	PMX_BONE_INFO_GRP = 5000,
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
	TAIL_INDEX,//�ӹ�������
	TAIL_POSITION,//���λ��
	TAIL_IS_INDEX = 0,//�������ӹ���
	TAIL_IS_POSITION = 1//���������λ��
};
#endif _PMX_BONE_TAG_H_
