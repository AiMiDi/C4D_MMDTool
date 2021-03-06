CONTAINER VMD_Cam_Obj {
	NAME VMD_Cam_Obj;
	INCLUDE Obase;

	GROUP VMD_CAM_OBJ_ANIMATION_GRP {
		DEFAULT 1;

		LONG VMD_CAM_OBJ_FRAME_ON {
		}

		LONG VMD_CAM_OBJ_CURVE_TYPE {
			ANIM OFF;
			MIN 0;
			MAX 5;

			CYCLE {
				VMD_CAM_OBJ_XCURVE;
				VMD_CAM_OBJ_YCURVE;
				VMD_CAM_OBJ_ZCURVE;
				VMD_CAM_OBJ_RCURVE;
				VMD_CAM_OBJ_DCURVE;
				VMD_CAM_OBJ_VCURVE;
				VMD_CAM_OBJ_ACURVE;
			}
		}

		GROUP {
			SPLINE VMD_CAM_OBJ_SPLINE {
				ANIM OFF;
				SHOWGRID_H;
				SHOWGRID_V;
				MINSIZE_H 350;
				MINSIZE_V 350;
				SQUARE;
			}

			GROUP {
				COLUMNS 4;

				BUTTON VMD_CAM_OBJ_INIT_CURVE_BUTTON {
				}

				BUTTON VMD_CAM_OBJ_REGISTER_CURVE_BUTTON {
				}

				BUTTON VMD_CAM_OBJ_DELETE_CURVE_BUTTON {
				}

				BUTTON VMD_CAM_OBJ_UPDATE_CURVE_BUTTON {
				}
			}
		}
	}
}
