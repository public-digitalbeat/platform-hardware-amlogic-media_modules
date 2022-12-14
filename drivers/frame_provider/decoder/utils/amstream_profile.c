/*
 * Copyright (C) 2017 Amlogic, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * Description:
 */
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/amlogic/media/utils/amstream.h>

static const struct codec_profile_t *vcodec_profile[SUPPORT_VDEC_NUM] = { 0 };

static int vcodec_profile_idx;

ssize_t vcodec_profile_read(char *buf)
{
	char *pbuf = buf;
	int i = 0;

	for (i = 0; i < vcodec_profile_idx; i++) {
		pbuf += snprintf(pbuf, PAGE_SIZE - (pbuf - buf), "%s:%s;\n", vcodec_profile[i]->name,
						vcodec_profile[i]->profile);
	}

	return pbuf - buf;
}
EXPORT_SYMBOL(vcodec_profile_read);

int vcodec_profile_register(const struct codec_profile_t *vdec_profile)
{
	if (vcodec_profile_idx < SUPPORT_VDEC_NUM) {
		vcodec_profile[vcodec_profile_idx] = vdec_profile;
		vcodec_profile_idx++;
		pr_debug("regist %s codec profile\n", vdec_profile->name);

	}

	return 0;
}
EXPORT_SYMBOL(vcodec_profile_register);

bool is_support_profile(char *name)
{
	int ret = 0;
	int i, size = ARRAY_SIZE(vcodec_profile);

	for (i = 0; i < size; i++) {
		if (!vcodec_profile[i])
			break;
		if (!strcmp(name, vcodec_profile[i]->name))
			return true;
	}
	return ret;
}
EXPORT_SYMBOL(is_support_profile);
