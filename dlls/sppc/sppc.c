/*
 *
 * Copyright 2008 Alistair Leslie-Hughes
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include <stdarg.h>

#include "ntstatus.h"
#define WIN32_NO_STATUS
#include "windef.h"
#include "winbase.h"
#include "winternl.h"
#include "wine/debug.h"

#include "slpublic.h"
#include "slerror.h"

WINE_DEFAULT_DEBUG_CHANNEL(slc);

HRESULT WINAPI SLGetLicensingStatusInformation(HSLC handle, const SLID *app, const SLID *product,
                                               LPCWSTR name, UINT *count, SL_LICENSING_STATUS **status)
{
    FIXME("(%p %p %p %s %p %p) stub\n", handle, app, product, debugstr_w(name), count, status );

    return SL_E_RIGHT_NOT_CONSUMED;
}

HRESULT WINAPI SLGetPolicyInformation(HSLC handle, PCWSTR policyName, SLDATATYPE *slDataType, UINT *dataSize, PBYTE *data)
{
    FIXME("(%p %s %p %p %p) stub\n", handle, debugstr_w(policyName), slDataType, dataSize, data);

    return SL_E_VALUE_NOT_FOUND;
}

HRESULT WINAPI SLGetPolicyInformationDWORD(HSLC handle, PCWSTR policyName, DWORD *ret)
{
    UNICODE_STRING nameW;
    NTSTATUS status;
    ULONG type, len;

    FIXME("(%p %s %p) stub\n", handle, debugstr_w(policyName), ret);

    if(!handle || !policyName || !ret)
        return E_INVALIDARG;
    if (!policyName[0])
        return SL_E_RIGHT_NOT_GRANTED;

    RtlInitUnicodeString(&nameW, policyName);
    status = NtQueryLicenseValue(&nameW, &type, ret, sizeof(DWORD), &len);

    if(status == STATUS_OBJECT_NAME_NOT_FOUND)
        return SL_E_VALUE_NOT_FOUND;
    if((!status || status == STATUS_BUFFER_TOO_SMALL) && (type != REG_DWORD))
        return SL_E_DATATYPE_MISMATCHED;

    return status ? E_FAIL : S_OK;
}

HRESULT WINAPI SLLoadApplicationPolicies(const SLID *app, const SLID *product, DWORD flags, HSLP *handle)
{
    FIXME("(%p %p %lx %p) stub\n", app, product, flags, handle);

    return SL_E_APPLICATION_POLICIES_MISSING;
}

HRESULT WINAPI SLOpen(HSLC *handle)
{
    FIXME("(%p) stub\n", handle );

    if (!handle)
        return E_INVALIDARG;

    *handle = (HSLC)0xdeadbeef;

    return S_OK;
}

HRESULT WINAPI SLClose(HSLC handle)
{
    FIXME("(%p) stub\n", handle );

    return S_OK;
}

HRESULT WINAPI SLConsumeRight(HSLC handle, const SLID *app, const SLID *product, PCWSTR rightName, PVOID reserved)
{
    FIXME("(%p, %p, %p, %s, %p) stub\n", handle, app, product, debugstr_w(rightName), reserved);

    if (!handle)
        return E_INVALIDARG;

    /* return SL_E_PRODUCT_SKU_NOT_INSTALLED; */
    return S_OK;
}

HRESULT WINAPI SLPersistApplicationPolicies(const SLID *app, const SLID *product, DWORD flags)
{
    FIXME("(%s,%s,%lx) stub\n", wine_dbgstr_guid(app), wine_dbgstr_guid(product), flags);

    if (!app)
        return E_INVALIDARG;

    return S_OK;
}

HRESULT WINAPI SLSetAuthenticationData(HSLC *handle, UINT *dataSize, PBYTE *data) 
{
    FIXME("(%p %p %p) stub\n", handle, dataSize, data);

    return SL_E_NOT_SUPPORTED;
}

HRESULT WINAPI SLUnloadApplicationPolicies(HSLP handle, DWORD flags)
{
    FIXME("(%p %lx) stub\n", handle, flags);

    return S_OK;
}
