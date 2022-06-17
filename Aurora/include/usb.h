/**
 * BSD 2-Clause License
 *
 * Copyright (c) 2022, Manas Kamal Choudhury
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 **/

#ifndef  __USB_H__
#define  __USB_H__

/* Standard USB Requests */
#define USB_BM_REQUEST_INPUT  0x80
#define USB_BM_REQUEST_STANDARD 0
#define USB_BM_REQUEST_CLASS  0x20
#define USB_BM_REQUEST_VENDOR 0x40
#define USB_BM_REQUEST_DEVICE  0
#define USB_BM_REQUEST_INTERFACE 1
#define USB_BM_REQUEST_ENDPOINT 2
#define USB_BM_REQUEST_VENDORSPEC  0x1F

#define USB_BREQUEST_GET_STATUS  0
#define USB_BREQUEST_CLEAR_FEATURE 1
#define USB_BREQUEST_SET_FEATURE 3
#define USB_BREQUEST_SET_ADDRESS 5
#define USB_BREQUEST_GET_DESCRIPTOR 6
#define USB_BREQUEST_SET_DESCRIPTOR 7
#define USB_BREQUEST_GET_CONFIGURATION 8
#define USB_BREQUEST_SET_CONFIGURATION 9
#define USB_BREQUEST_GET_INTERFACE  10
#define USB_BREQUEST_SET_INTERFACE  11

#define USB_DESCRIPTOR_DEVICE  1
#define USB_DESCRIPTOR_CONFIGURATION 2
#define USB_DESCRIPTOR_STRING  3
#define USB_DESCRIPTOR_INTERFACE 4
#define USB_DESCRIPTOR_ENDPOINT  5

#define USB_DESCRIPTOR_WVALUE(type,index) ((type << 8) | index)


#endif