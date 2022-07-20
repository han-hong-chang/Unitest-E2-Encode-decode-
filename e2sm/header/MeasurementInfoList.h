/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-KPM-IEs"
 * 	found in "O-RAN.WG3.E2SM-KPM-v02.01.asn1"
 * 	`asn1c -pdu=auto -fcompound-names -findirect-choice -gen-PER -gen-OER -no-gen-example`
 */

#ifndef	_MeasurementInfoList_H_
#define	_MeasurementInfoList_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct MeasurementInfoItem;

/* MeasurementInfoList */
typedef struct MeasurementInfoList {
	A_SEQUENCE_OF(struct MeasurementInfoItem) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MeasurementInfoList_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MeasurementInfoList;
extern asn_SET_OF_specifics_t asn_SPC_MeasurementInfoList_specs_1;
extern asn_TYPE_member_t asn_MBR_MeasurementInfoList_1[1];
extern asn_per_constraints_t asn_PER_type_MeasurementInfoList_constr_1;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "MeasurementInfoItem.h"

#endif	/* _MeasurementInfoList_H_ */
#include <asn_internal.h>
