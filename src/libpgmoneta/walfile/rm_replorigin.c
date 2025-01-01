/*
 * Copyright (C) 2025 The pgmoneta community
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list
 * of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may
 * be used to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <walfile/rm.h>
#include <walfile/rm_replorigin.h>
#include <utils.h>

char*
pgmoneta_wal_replorigin_desc(char* buf, struct decoded_xlog_record* record)
{
   char* rec = XLOG_REC_GET_DATA(record);
   uint8_t info = XLOG_REC_GET_INFO(record) & ~XLR_INFO_MASK;

   switch (info)
   {
      case XLOG_REPLORIGIN_SET:
      {
         struct xl_replorigin_set* xlrec;

         xlrec = (struct xl_replorigin_set*) rec;

         buf = pgmoneta_format_and_append(buf, "set %u; lsn %X/%X; force: %d",
                                          xlrec->node_id,
                                          LSN_FORMAT_ARGS(xlrec->remote_lsn),
                                          xlrec->force);
         break;
      }
      case XLOG_REPLORIGIN_DROP:
      {
         struct xl_replorigin_drop* xlrec;

         xlrec = (struct xl_replorigin_drop*) rec;

         buf = pgmoneta_format_and_append(buf, "drop %u", xlrec->node_id);
         break;
      }
   }
   return buf;
}
