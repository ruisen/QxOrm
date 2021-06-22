#include "../include/precompiled.h"

#include "../include/blog.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_BLOG(blog)

void logCustomSqlCallback(qx::IxDataMemberSqlCallbackParams & params, const QString & fctName)
{
   QString msg = "-- " + fctName + " : " + params.pDataMember->getNameParent() + "::" + params.pDataMember->getName() + " --";
   msg += "\nSQL query generated by QxOrm library for this data member : " + params.sSQL;
   if (params.pSqlQueryBuilder) { msg += "\nCurrent building full SQL query (not finished yet) : " + params.pSqlQueryBuilder->getCurrentBuildingSql(); }
   msg += "\n";
   qDebug(qPrintable(msg));
}

void myCustomGetSqlName(qx::IxDataMemberSqlCallbackParams & params)
{
   logCustomSqlCallback(params, "myCustomGetSqlName");
}

void myCustomGetSqlTablePointNameAsAlias(qx::IxDataMemberSqlCallbackParams & params)
{
   logCustomSqlCallback(params, "myCustomGetSqlTablePointNameAsAlias");
}

void myCustomGetSqlNameEqualToPlaceHolder(qx::IxDataMemberSqlCallbackParams & params)
{
   logCustomSqlCallback(params, "myCustomGetSqlNameEqualToPlaceHolder");
}

void myCustomGetSqlAliasEqualToPlaceHolder(qx::IxDataMemberSqlCallbackParams & params)
{
   logCustomSqlCallback(params, "myCustomGetSqlAliasEqualToPlaceHolder");
}

void myCustomGetSqlAlias(qx::IxDataMemberSqlCallbackParams & params)
{
   logCustomSqlCallback(params, "myCustomGetSqlAlias");
}

namespace qx {
template <> void register_class(QxClass<blog> & t)
{
   t.id(& blog::m_id, blog::str_composite_key());

   t.data(& blog::m_text, "blog_text");
   qx::IxDataMember * pData = t.data(& blog::m_dt_creation, "date_creation");

   pData->customGetSqlName(myCustomGetSqlName);
   pData->customGetSqlTablePointNameAsAlias(myCustomGetSqlTablePointNameAsAlias);
   pData->customGetSqlNameEqualToPlaceHolder(myCustomGetSqlNameEqualToPlaceHolder);
   pData->customGetSqlAliasEqualToPlaceHolder(myCustomGetSqlAliasEqualToPlaceHolder);
   pData->customGetSqlAlias(myCustomGetSqlAlias);

   t.relationManyToOne(& blog::m_author, author::str_composite_key());
   t.relationOneToMany(& blog::m_commentX, comment::str_composite_key(), blog::str_composite_key());
   t.relationManyToMany(& blog::m_categoryX, "list_category", "category_blog", blog::str_composite_key(), category::str_composite_key());
}}
