CONTAINER PMX_Model_Tag {
	NAME PMX_Model_Tag;
	INCLUDE Texpression;

	GROUP MODEL_INFO_GRP {
		DEFAULT 1;

		REAL PMX_VERSION {
			ANIM OFF;
			UNIT REAL;
			MIN 2.0;
			STEP 0.1;
			MAX 2.1;
		}

		STRING MODEL_NAME_LOCAL {
			ANIM OFF;
		}

		STRING MODEL_NAME_UNIVERSAL {
			ANIM OFF;
		}

		STRING COMMENTS_LOCAL {
			ANIM OFF;
			CUSTOMGUI MULTISTRING;
			SCALE_H;
			SCALE_V;
		}

		STRING COMMENTS_UNIVERSAL {
			ANIM OFF;
			CUSTOMGUI MULTISTRING;
			SCALE_H;
			SCALE_V;
		}
	}

	GROUP MODEL_IK_GRP {
	}
}
