/*
 * Copyright (c) 2016-2021 The Linux Foundation. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _HAL_BE_RX_H_
#define _HAL_BE_RX_H_

#include "hal_be_hw_headers.h"
#include "hal_rx.h"

/*
 * macro to set the cookie into the rxdma ring entry
 */
#define HAL_RXDMA_COOKIE_SET(buff_addr_info, cookie) \
		((*(((unsigned int *)buff_addr_info) + \
		(BUFFER_ADDR_INFO_SW_BUFFER_COOKIE_OFFSET >> 2))) &= \
		~BUFFER_ADDR_INFO_SW_BUFFER_COOKIE_MASK); \
		((*(((unsigned int *)buff_addr_info) + \
		(BUFFER_ADDR_INFO_SW_BUFFER_COOKIE_OFFSET >> 2))) |= \
		(cookie << BUFFER_ADDR_INFO_SW_BUFFER_COOKIE_LSB) & \
		BUFFER_ADDR_INFO_SW_BUFFER_COOKIE_MASK)

/*
 * macro to set the manager into the rxdma ring entry
 */
#define HAL_RXDMA_MANAGER_SET(buff_addr_info, manager) \
		((*(((unsigned int *)buff_addr_info) + \
		(BUFFER_ADDR_INFO_RETURN_BUFFER_MANAGER_OFFSET >> 2))) &= \
		~BUFFER_ADDR_INFO_RETURN_BUFFER_MANAGER_MASK); \
		((*(((unsigned int *)buff_addr_info) + \
		(BUFFER_ADDR_INFO_RETURN_BUFFER_MANAGER_OFFSET >> 2))) |= \
		(manager << BUFFER_ADDR_INFO_RETURN_BUFFER_MANAGER_LSB) & \
		BUFFER_ADDR_INFO_RETURN_BUFFER_MANAGER_MASK)

#define HAL_RX_ERROR_STATUS_GET(reo_desc)			\
	(_HAL_MS((*_OFFSET_TO_WORD_PTR(reo_desc,		\
		REO_DESTINATION_RING_REO_PUSH_REASON_OFFSET)),\
		REO_DESTINATION_RING_REO_PUSH_REASON_MASK,	\
		REO_DESTINATION_RING_REO_PUSH_REASON_LSB))

#define HAL_RX_BUF_COOKIE_GET(buff_addr_info)			\
	(_HAL_MS((*_OFFSET_TO_WORD_PTR(buff_addr_info,		\
		BUFFER_ADDR_INFO_SW_BUFFER_COOKIE_OFFSET)),	\
		BUFFER_ADDR_INFO_SW_BUFFER_COOKIE_MASK,	\
		BUFFER_ADDR_INFO_SW_BUFFER_COOKIE_LSB))

#define HAL_RX_BUF_RBM_GET(buff_addr_info)			\
	(_HAL_MS((*_OFFSET_TO_WORD_PTR(buff_addr_info,		\
		BUFFER_ADDR_INFO_RETURN_BUFFER_MANAGER_OFFSET)),\
		BUFFER_ADDR_INFO_RETURN_BUFFER_MANAGER_MASK,	\
		BUFFER_ADDR_INFO_RETURN_BUFFER_MANAGER_LSB))

/* TODO: Convert the following structure fields accesseses to offsets */

#define HAL_RX_REO_BUF_COOKIE_GET(reo_desc)	\
	(HAL_RX_BUF_COOKIE_GET(&		\
	(((struct reo_destination_ring *)	\
		reo_desc)->buf_or_link_desc_addr_info)))

#define HAL_RX_MSDU_DESC_IP_CHKSUM_FAIL_GET(msdu_desc_info_ptr)	\
	(_HAL_MS((*_OFFSET_TO_WORD_PTR((msdu_desc_info_ptr),	\
		RX_MSDU_DESC_INFO_IP_CHKSUM_FAIL_OFFSET)),	\
		RX_MSDU_DESC_INFO_IP_CHKSUM_FAIL_MASK,	\
		RX_MSDU_DESC_INFO_IP_CHKSUM_FAIL_LSB))

#define HAL_RX_REO_IP_CHKSUM_FAIL_GET(ring_desc)	\
	(HAL_RX_MSDU_DESC_IP_CHKSUM_FAIL_GET(&		\
	((struct reo_destination_ring *)ring_desc)->rx_msdu_desc_info_details))

#define HAL_RX_MSDU_DESC_TCP_UDP_CHKSUM_FAIL_GET(msdu_desc_info_ptr)	\
	(_HAL_MS((*_OFFSET_TO_WORD_PTR((msdu_desc_info_ptr),		\
		RX_MSDU_DESC_INFO_TCP_UDP_CHKSUM_FAIL_OFFSET)),	\
		RX_MSDU_DESC_INFO_TCP_UDP_CHKSUM_FAIL_MASK,	\
		RX_MSDU_DESC_INFO_TCP_UDP_CHKSUM_FAIL_LSB))

#define HAL_RX_REO_TCP_UDP_CHKSUM_FAIL_GET(ring_desc)	\
	(HAL_RX_MSDU_DESC_TCP_UDP_CHKSUM_FAIL_GET(&		\
	((struct reo_destination_ring *)ring_desc)->rx_msdu_desc_info_details))

#define HAL_RX_MSDU_DESC_AMPDU_FLAG_GET(mpdu_info_ptr)		\
	(_HAL_MS((*_OFFSET_TO_WORD_PTR((mpdu_info_ptr),		\
		RX_MPDU_DESC_INFO_AMPDU_FLAG_OFFSET)),		\
		RX_MPDU_DESC_INFO_AMPDU_FLAG_MASK,		\
		RX_MPDU_DESC_INFO_AMPDU_FLAG_LSB))

#define HAL_RX_MPDU_DESC_PEER_META_DATA_GET(mpdu_info_ptr)	\
	((mpdu_info_ptr					\
	[RX_MPDU_DESC_INFO_PEER_META_DATA_OFFSET >> 2] & \
	RX_MPDU_DESC_INFO_PEER_META_DATA_MASK) >> \
	RX_MPDU_DESC_INFO_PEER_META_DATA_LSB)

#define HAL_RX_MPDU_MSDU_COUNT_GET(mpdu_info_ptr) \
	((mpdu_info_ptr[RX_MPDU_DESC_INFO_MSDU_COUNT_OFFSET >> 2] & \
	RX_MPDU_DESC_INFO_MSDU_COUNT_MASK) >> \
	RX_MPDU_DESC_INFO_MSDU_COUNT_LSB)

#define HAL_RX_MPDU_FRAGMENT_FLAG_GET(mpdu_info_ptr) \
	(mpdu_info_ptr[RX_MPDU_DESC_INFO_FRAGMENT_FLAG_OFFSET >> 2] & \
	RX_MPDU_DESC_INFO_FRAGMENT_FLAG_MASK)

#define HAL_RX_MPDU_RETRY_BIT_GET(mpdu_info_ptr) \
	(mpdu_info_ptr[RX_MPDU_DESC_INFO_MPDU_RETRY_BIT_OFFSET >> 2] & \
	RX_MPDU_DESC_INFO_MPDU_RETRY_BIT_MASK)

#define HAL_RX_MPDU_AMPDU_FLAG_GET(mpdu_info_ptr) \
	(mpdu_info_ptr[RX_MPDU_DESC_INFO_AMPDU_FLAG_OFFSET >> 2] & \
	RX_MPDU_DESC_INFO_AMPDU_FLAG_MASK)

#define HAL_RX_MPDU_RAW_MPDU_GET(mpdu_info_ptr) \
	(mpdu_info_ptr[RX_MPDU_DESC_INFO_RAW_MPDU_OFFSET >> 2] & \
	RX_MPDU_DESC_INFO_RAW_MPDU_MASK)

#define HAL_RX_MPDU_BAR_FRAME_GET(mpdu_info_ptr) \
	((mpdu_info_ptr[RX_MPDU_DESC_INFO_BAR_FRAME_OFFSET >> 2] & \
	RX_MPDU_DESC_INFO_BAR_FRAME_MASK) >> \
	RX_MPDU_DESC_INFO_BAR_FRAME_LSB)

/*
 * NOTE: None of the following _GET macros need a right
 * shift by the corresponding _LSB. This is because, they are
 * finally taken and "OR'ed" into a single word again.
 */
#define HAL_RX_MSDU_CONTINUATION_FLAG_SET(msdu_info_ptr, val)		\
	((*(((uint32_t *)msdu_info_ptr) +				\
		(RX_MSDU_DESC_INFO_MSDU_CONTINUATION_OFFSET >> 2))) |= \
		((val) << RX_MSDU_DESC_INFO_MSDU_CONTINUATION_LSB) & \
		RX_MSDU_DESC_INFO_MSDU_CONTINUATION_MASK)

#define HAL_RX_MSDU_CONTINUATION_FLAG_GET(msdu_info_ptr)	\
	((*_OFFSET_TO_WORD_PTR(msdu_info_ptr,			\
		RX_MSDU_DESC_INFO_MSDU_CONTINUATION_OFFSET)) & \
		RX_MSDU_DESC_INFO_MSDU_CONTINUATION_MASK)

#define HAL_RX_MSDU_REO_DST_IND_GET(msdu_info_ptr)	\
	(_HAL_MS((*_OFFSET_TO_WORD_PTR(msdu_info_ptr,	\
	RX_MSDU_EXT_DESC_INFO_REO_DESTINATION_INDICATION_OFFSET)),	\
	RX_MSDU_EXT_DESC_INFO_REO_DESTINATION_INDICATION_MASK,		\
	RX_MSDU_EXT_DESC_INFO_REO_DESTINATION_INDICATION_LSB))

#define HAL_RX_MSDU_SA_IS_VALID_FLAG_GET(msdu_info_ptr)		\
	((*_OFFSET_TO_WORD_PTR(msdu_info_ptr,			\
		RX_MSDU_DESC_INFO_SA_IS_VALID_OFFSET)) &	\
		RX_MSDU_DESC_INFO_SA_IS_VALID_MASK)

#define HAL_RX_MSDU_DA_IS_VALID_FLAG_GET(msdu_info_ptr)		\
	((*_OFFSET_TO_WORD_PTR(msdu_info_ptr,			\
		RX_MSDU_DESC_INFO_DA_IS_VALID_OFFSET)) &	\
		RX_MSDU_DESC_INFO_DA_IS_VALID_MASK)

#define HAL_RX_MSDU_DA_IS_MCBC_FLAG_GET(msdu_info_ptr)		\
	((*_OFFSET_TO_WORD_PTR(msdu_info_ptr,			\
		RX_MSDU_DESC_INFO_DA_IS_MCBC_OFFSET)) &	\
		RX_MSDU_DESC_INFO_DA_IS_MCBC_MASK)

#define HAL_RX_MPDU_ENCRYPT_TYPE_GET(_rx_mpdu_info)	\
	(_HAL_MS((*_OFFSET_TO_WORD_PTR(_rx_mpdu_info,	\
	RX_MPDU_INFO_ENCRYPT_TYPE_OFFSET)),		\
	RX_MPDU_INFO_ENCRYPT_TYPE_MASK,		\
	RX_MPDU_INFO_ENCRYPT_TYPE_LSB))

#define HAL_RX_MSDU_DESC_INFO_SET(_msdu_info_ptr, _field, _val)		\
	HAL_RX_FLD_SET(_msdu_info_ptr, RX_MSDU_DESC_INFO,		\
			_field, _val)

#define HAL_RX_MPDU_DESC_INFO_SET(_mpdu_info_ptr, _field, _val)		\
	HAL_RX_FLD_SET(_mpdu_info_ptr, RX_MPDU_DESC_INFO,		\
			_field, _val)

/**
 * enum hal_be_rx_wbm_error_source: Indicates which module initiated the
 * release of this buffer or descriptor
 *
 * @ HAL_BE_RX_WBM_ERR_SRC_RXDMA: RXDMA released this buffer or descriptor
 * @ HAL_BE_RX_WBM_ERR_SRC_REO: REO released this buffer or descriptor
 * @ HAL_BE_RX_WBM_ERR_SRC_FW_RX: FW released this buffer or descriptor from the
 *				RX path
 * @ HAL_BE_RX_WBM_ERR_SRC_SW_RX: SW released this buffer or descriptor from the
 *				RX path
 * @ HAL_BE_RX_WBM_ERR_SRC_TQM : TQM released this buffer or descriptor
 * @ HAL_BE_RX_WBM_ERR_SRC_FW_TX: FW released this buffer or descriptor from the
 *				RX path
 * @ HAL_BE_RX_WBM_ERR_SRC_SW_TX: SW released this buffer or descriptor from the
 *				RX path
 */
enum hal_be_rx_wbm_error_source {
	HAL_BE_RX_WBM_ERR_SRC_RXDMA = 0,
	HAL_BE_RX_WBM_ERR_SRC_REO,
	HAL_BE_RX_WBM_ERR_SRC_FW_RX,
	HAL_BE_RX_WBM_ERR_SRC_SW_RX,
	HAL_BE_RX_WBM_ERR_SRC_TQM,
	HAL_BE_RX_WBM_ERR_SRC_FW_TX,
	HAL_BE_RX_WBM_ERR_SRC_SW_TX,
};

/**
 * enum hal_be_wbm_release_dir - Direction of the buffer which was released to
 *			wbm.
 * @HAL_BE_WBM_RELEASE_DIR_RX: Buffer released to WBM due to error
 * @HAL_BE_WBM_RELEASE_DIR_TX: Buffer released to WBM from TX path
 */
enum hal_be_wbm_release_dir {
	HAL_BE_WBM_RELEASE_DIR_RX,
	HAL_BE_WBM_RELEASE_DIR_TX,
};

static inline uint32_t hal_rx_get_mpdu_flags(uint32_t *mpdu_info)
{
	uint32_t mpdu_flags = 0;

	if (HAL_RX_MPDU_FRAGMENT_FLAG_GET(mpdu_info))
		mpdu_flags |= HAL_MPDU_F_FRAGMENT;

	if (HAL_RX_MPDU_RETRY_BIT_GET(mpdu_info))
		mpdu_flags |= HAL_MPDU_F_RETRY_BIT;

	if (HAL_RX_MPDU_AMPDU_FLAG_GET(mpdu_info))
		mpdu_flags |= HAL_MPDU_F_AMPDU_FLAG;

	if (HAL_RX_MPDU_RAW_MPDU_GET(mpdu_info))
		mpdu_flags |= HAL_MPDU_F_RAW_AMPDU;

	return mpdu_flags;
}

/*******************************************************************************
 * RX REO ERROR APIS
 ******************************************************************************/

/**
 * hal_rx_msdu_reo_dst_ind_get: Gets the REO
 * destination ring ID from the msdu desc info
 *
 * @msdu_link_desc : Opaque cookie pointer used by HAL to get to
 * the current descriptor
 *
 * Return: dst_ind (REO destination ring ID)
 */
static inline uint32_t
hal_rx_msdu_reo_dst_ind_get(hal_soc_handle_t hal_soc_hdl, void *msdu_link_desc)
{
	struct hal_soc *hal_soc = (struct hal_soc *)hal_soc_hdl;
	struct rx_msdu_details *msdu_details;
	struct rx_msdu_desc_info *msdu_desc_info;
	struct rx_msdu_link *msdu_link = (struct rx_msdu_link *)msdu_link_desc;
	uint32_t dst_ind;

	msdu_details = hal_rx_link_desc_msdu0_ptr(msdu_link, hal_soc);

	/* The first msdu in the link should exsist */
	msdu_desc_info = hal_rx_msdu_ext_desc_info_get_ptr(&msdu_details[0],
							   hal_soc);
	dst_ind = HAL_RX_MSDU_REO_DST_IND_GET(msdu_desc_info);
	return dst_ind;
}

#define HAL_RX_REO_BUF_TYPE_GET(reo_desc) (((*(((uint32_t *)reo_desc) + \
		(REO_DESTINATION_RING_REO_DEST_BUFFER_TYPE_OFFSET >> 2))) & \
		REO_DESTINATION_RING_REO_DEST_BUFFER_TYPE_MASK) >> \
		REO_DESTINATION_RING_REO_DEST_BUFFER_TYPE_LSB)

#define HAL_RX_REO_QUEUE_NUMBER_GET(reo_desc) (((*(((uint32_t *)reo_desc) + \
	(REO_DESTINATION_RING_RX_MPDU_DESC_INFO_DETAILS_TID_OFFSET >> 2))) & \
	REO_DESTINATION_RING_RX_MPDU_DESC_INFO_DETAILS_TID_MASK) >> \
	REO_DESTINATION_RING_RX_MPDU_DESC_INFO_DETAILS_TID_LSB)

#define HAL_RX_REO_ERROR_GET(reo_desc) (((*(((uint32_t *)reo_desc) + \
		(REO_DESTINATION_RING_REO_ERROR_CODE_OFFSET >> 2))) & \
		REO_DESTINATION_RING_REO_ERROR_CODE_MASK) >> \
		REO_DESTINATION_RING_REO_ERROR_CODE_LSB)

/*
 * hal_rx_msdu_link_desc_reinject: Re-injects the MSDU link descriptor to
 * REO entrance ring
 *
 * @ soc: HAL version of the SOC pointer
 * @ pa: Physical address of the MSDU Link Descriptor
 * @ cookie: SW cookie to get to the virtual address
 * @ error_enabled_reo_q: Argument to determine whether this needs to go
 * to the error enabled REO queue
 *
 * Return: void
 */
static inline void
hal_rx_msdu_link_desc_reinject(struct hal_soc *soc, uint64_t pa,
			       uint32_t cookie, bool error_enabled_reo_q)
{
	/* TODO */
}

#define HAL_RX_WBM_FIRST_MSDU_GET(wbm_desc)		\
	(((*(((uint32_t *)wbm_desc) +			\
	(WBM_RELEASE_RING_FIRST_MSDU_OFFSET >> 2))) & \
	WBM_RELEASE_RING_FIRST_MSDU_MASK) >>		\
	WBM_RELEASE_RING_FIRST_MSDU_LSB)

#define HAL_RX_WBM_LAST_MSDU_GET(wbm_desc)		\
	(((*(((uint32_t *)wbm_desc) +			\
	(WBM_RELEASE_RING_LAST_MSDU_OFFSET >> 2))) &  \
	WBM_RELEASE_RING_LAST_MSDU_MASK) >>		\
	WBM_RELEASE_RING_LAST_MSDU_LSB)

#define HAL_RX_WBM_BUF_COOKIE_GET(wbm_desc) \
	HAL_RX_BUF_COOKIE_GET(&((struct wbm_release_ring *) \
	wbm_desc)->released_buff_or_desc_addr_info)

#endif /* _HAL_BE_RX_H_ */